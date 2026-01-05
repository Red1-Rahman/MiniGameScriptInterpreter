%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

extern FILE *yyin;

#define MAX_GRID_SIZE 100

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

// Grid size (dynamic)
int GRID_SIZE = 10;

// Player position and stats
int player_x = 0, player_y = 0;
char player_symbol = 'P';
char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
int player_health = 100;
int max_health = 100;
char inventory[10][50];
int inventory_count = 0;
int sound_enabled = 1;
int game_time = 0;
int enemies_count = 0;

// Mission generation system (inspired by Dormans' paper)
typedef struct {
    char type[20];     // "key", "lock", "boss", "treasure", "challenge"
    char name[50];
    int x, y;          // spatial location
    int completed;
    int required_task; // dependency (-1 if none)
} Task;

Task mission_tasks[20];
int task_count = 0;
int current_mission_step = 0;
char mission_theme[50] = "adventure";
int adaptive_difficulty = 1;
int player_skill_level = 1;

// Procedural generation parameters
int generation_seed = 0;
int dungeon_complexity = 3;
char generation_style[20] = "balanced";

// Teleport points
typedef struct {
    char name[20];
    int x, y;
} TeleportPoint;
TeleportPoint teleports[10];
int teleport_count = 0;

// Variable table
typedef struct {
    char name[50];
    int value;
} Var;
Var variables[50];
int var_count = 0;

// Score for collecting items
int player_score = 0;

// Function prototypes
int yylex();
void yyerror(const char *s);
int get_var(char *name);
void set_var(char *name, int value);
void add_var(char *name, int value);
void subtract_var(char *name, int value);
int eval_expr(int left, char *op, int right);
int eval_arith(int left, char *op, int right);
void init_grid();
void print_grid();
void move_player(char *dir);
void place_object(char *type, int x, int y);
void set_grid_size(int size);
void change_health(int amount);
void add_to_inventory(char *item);
void use_item(char *item);
int generate_random(int min, int max);
void play_sound();
void wait_time(int seconds);
void create_teleport(char *name, int x, int y);
void teleport_to(char *name);
void show_status();
void attack_enemies_nearby();
void generate_mission(char *theme, int complexity);
void generate_dungeon_space(int size, char *style);
void place_mission_objects();
void check_mission_progress();
void adapt_difficulty();
void show_mission_status();
void complete_task(int task_id);
int find_task_by_name(char *name);
void procedural_populate(int density, char *type);

int interactive_mode = 0;
int exit_interactive = 0;
FILE *script_file = NULL;

// For storing loop body
char loop_buffer[4096];
int in_loop = 0;
int loop_count = 0;

%}

%union {
    char* str;
    int num;
}

%token <str> MOVE SAY SET ADD SUBTRACT IF ENDIF EXIT IDENTIFIER STRING DIRECTION OPERATOR REPEAT ENDREPEAT PLACE OBJECT_TYPE ARITHOP GRIDSIZE HEALTH INVENTORY USE RANDOM SOUND WAIT TELEPORT STATUS ATTACK MISSION GENERATE THEME COMPLETE ADAPT POPULATE
%token <num> NUMBER

%type <num> expr
%left ARITHOP
%left '(' ')'

%%

script:
    commands
    ;

commands:
      /* empty */
    | commands command
    ;

expr:
      NUMBER                        { $$ = $1; }
    | IDENTIFIER                    { $$ = get_var($1); free($1); }
    | expr ARITHOP expr             { $$ = eval_arith($1, $2, $3); }
    | '(' expr ')'                  { $$ = $2; }
    ;

command:
      MOVE IDENTIFIER DIRECTION     { move_player($3); }
    | SAY STRING                   { printf(GREEN "%s\n" RESET, $2); free($2); }
    | SET IDENTIFIER expr          { set_var($2, $3); printf(GREEN "%s set to %d\n" RESET, $2, $3); free($2); }
    | ADD IDENTIFIER expr          { add_var($2, $3); printf(GREEN "%s updated to %d\n" RESET, $2, get_var($2)); free($2); }
    | SUBTRACT IDENTIFIER expr     { subtract_var($2, $3); printf(GREEN "%s updated to %d\n" RESET, $2, get_var($2)); free($2); }
    | GRIDSIZE expr                { set_grid_size($2); }
    | HEALTH expr                  { change_health($2); }
    | INVENTORY IDENTIFIER         { add_to_inventory($2); free($2); }
    | USE IDENTIFIER               { use_item($2); free($2); }
    | RANDOM IDENTIFIER expr expr  { set_var($2, generate_random($3, $4)); free($2); }
    | SOUND expr                   { sound_enabled = $2; printf(GREEN "Sound %s\n" RESET, $2 ? "enabled" : "disabled"); }
    | WAIT expr                    { wait_time($2); }
    | TELEPORT IDENTIFIER expr expr { create_teleport($2, $3, $4); free($2); }
    | TELEPORT IDENTIFIER          { teleport_to($2); free($2); }
    | STATUS                       { show_status(); }
    | ATTACK                       { attack_enemies_nearby(); }
    | MISSION THEME IDENTIFIER     { strcpy(mission_theme, $3); generate_mission($3, dungeon_complexity); free($3); }
    | GENERATE IDENTIFIER expr     { if(strcmp($2, "dungeon") == 0) generate_dungeon_space($3, generation_style); free($2); }
    | COMPLETE IDENTIFIER          { int task_id = find_task_by_name($2); if(task_id >= 0) complete_task(task_id); free($2); }
    | ADAPT expr                   { adaptive_difficulty = $2; if($2) adapt_difficulty(); printf(GREEN "Adaptive difficulty %s\n" RESET, $2 ? "enabled" : "disabled"); }
    | POPULATE IDENTIFIER expr     { procedural_populate($3, $2); free($2); }
    | IF IDENTIFIER OPERATOR expr commands ENDIF
        { if(eval_expr(get_var($2), $3, $4)) { /* already executed commands */ } }
    | REPEAT expr commands ENDREPEAT
        { 
            // Note: This simple implementation executes loop body once during parsing
            // For proper loop execution, you'd need to store and re-execute the commands
            for(int i = 1; i < $2; i++) {
                printf(YELLOW "Loop iteration %d\n" RESET, i+1);
            }
        }
    | PLACE OBJECT_TYPE NUMBER NUMBER
        { place_object($2, $3, $4); }
    | EXIT
        { 
            if(interactive_mode) {
                exit_interactive = 1;
            } else {
                exit(0);
            }
        }
    ;

%%

// ---------------------- Enhanced Helper Functions ----------------------

void play_sound(){
    if(sound_enabled){
        printf("\a"); // Terminal beep
        fflush(stdout);
    }
}

int generate_random(int min, int max){
    if(max <= min) return min;
    return min + (rand() % (max - min + 1));
}

void wait_time(int seconds){
    printf(YELLOW "Waiting %d seconds...\n" RESET, seconds);
    for(int i = 0; i < seconds; i++){
        printf(".");
        fflush(stdout);
        usleep(1000000); // 1 second
    }
    printf("\n");
}

void change_health(int amount){
    player_health += amount;
    if(player_health > max_health) player_health = max_health;
    if(player_health < 0) player_health = 0;
    
    if(amount > 0){
        printf(GREEN "Health restored by %d! Current: %d/%d\n" RESET, amount, player_health, max_health);
        play_sound();
    } else if(amount < 0){
        printf(RED "Took %d damage! Current: %d/%d\n" RESET, -amount, player_health, max_health);
        play_sound();
    }
    
    if(player_health == 0){
        printf(RED "\n*** GAME OVER - You died! ***\n" RESET);
        if(!interactive_mode) exit(0);
    }
}

void add_to_inventory(char *item){
    if(inventory_count < 10){
        strcpy(inventory[inventory_count], item);
        inventory_count++;
        printf(GREEN "Added %s to inventory\n" RESET, item);
        play_sound();
    } else {
        printf(RED "Inventory full!\n" RESET);
    }
}

void use_item(char *item){
    for(int i = 0; i < inventory_count; i++){
        if(strcmp(inventory[i], item) == 0){
            printf(GREEN "Used %s\n" RESET, item);
            
            // Item effects
            if(strcmp(item, "potion") == 0){
                change_health(25);
            } else if(strcmp(item, "sword") == 0){
                printf(GREEN "Sword equipped! Attack power increased\n" RESET);
            } else if(strcmp(item, "key") == 0){
                printf(GREEN "Door unlocked!\n" RESET);
            }
            
            // Remove item from inventory
            for(int j = i; j < inventory_count - 1; j++){
                strcpy(inventory[j], inventory[j + 1]);
            }
            inventory_count--;
            play_sound();
            return;
        }
    }
    printf(RED "Item '%s' not found in inventory\n" RESET, item);
}

void create_teleport(char *name, int x, int y){
    if(teleport_count < 10 && x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE){
        strcpy(teleports[teleport_count].name, name);
        teleports[teleport_count].x = x;
        teleports[teleport_count].y = y;
        teleport_count++;
        grid[x][y] = 'T';
        printf(GREEN "Teleport point '%s' created at (%d, %d)\n" RESET, name, x, y);
        print_grid();
    }
}

void teleport_to(char *name){
    for(int i = 0; i < teleport_count; i++){
        if(strcmp(teleports[i].name, name) == 0){
            grid[player_x][player_y] = '.';
            player_x = teleports[i].x;
            player_y = teleports[i].y;
            grid[player_x][player_y] = player_symbol;
            printf(GREEN "Teleported to %s!\n" RESET, name);
            play_sound();
            print_grid();
            return;
        }
    }
    printf(RED "Teleport point '%s' not found\n" RESET, name);
}

void show_status(){
    printf(YELLOW "\n=== Player Status ===\n" RESET);
    printf("Position: (%d, %d)\n", player_x, player_y);
    printf("Health: %d/%d\n", player_health, max_health);
    printf("Score: %d\n", player_score);
    printf("Game Time: %d\n", game_time);
    printf("Inventory (%d/10): ", inventory_count);
    for(int i = 0; i < inventory_count; i++){
        printf("%s ", inventory[i]);
    }
    printf("\n");
    printf("Teleports available: ");
    for(int i = 0; i < teleport_count; i++){
        printf("%s ", teleports[i].name);
    }
    printf("\n" RESET);
    
    // Show mission status if active
    if(task_count > 0){
        show_mission_status();
    }
}

void attack_enemies_nearby(){
    int enemies_defeated = 0;
    // Check adjacent cells for enemies
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for(int i = 0; i < 4; i++){
        int nx = player_x + directions[i][0];
        int ny = player_y + directions[i][1];
        
        if(nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE){
            if(grid[nx][ny] == 'E'){
                grid[nx][ny] = '.';
                enemies_defeated++;
                player_score += 50;
                enemies_count--;
            }
        }
    }
    
    if(enemies_defeated > 0){
        printf(GREEN "Defeated %d enemies! Score: %d\n" RESET, enemies_defeated, player_score);
        play_sound();
        print_grid();
    } else {
        printf(RED "No enemies nearby to attack\n" RESET);
    }
}

int get_var(char *name){
    for(int i=0;i<var_count;i++)
        if(strcmp(variables[i].name,name)==0) return variables[i].value;
    return 0;
}

void set_var(char *name, int value){
    for(int i=0;i<var_count;i++)
        if(strcmp(variables[i].name,name)==0){ variables[i].value = value; return; }
    strcpy(variables[var_count].name,name);
    variables[var_count].value = value;
    var_count++;
}

void add_var(char *name, int value){
    for(int i=0;i<var_count;i++)
        if(strcmp(variables[i].name,name)==0){ variables[i].value += value; return; }
    strcpy(variables[var_count].name,name);
    variables[var_count].value = value;
    var_count++;
}

void subtract_var(char *name, int value){
    for(int i=0;i<var_count;i++)
        if(strcmp(variables[i].name,name)==0){ variables[i].value -= value; return; }
    strcpy(variables[var_count].name,name);
    variables[var_count].value = -value;
    var_count++;
}

int eval_expr(int left, char *op, int right){
    if(strcmp(op, "==")==0) return left==right;
    if(strcmp(op, "!=")==0) return left!=right;
    if(strcmp(op, ">")==0)  return left>right;
    if(strcmp(op, "<")==0)  return left<right;
    if(strcmp(op, ">=")==0) return left>=right;
    if(strcmp(op, "<=")==0) return left<=right;
    return 0;
}

int eval_arith(int left, char *op, int right){
    if(strcmp(op, "+")==0) return left + right;
    if(strcmp(op, "-")==0) return left - right;
    if(strcmp(op, "*")==0) return left * right;
    if(strcmp(op, "/")==0) return right != 0 ? left / right : 0;
    if(strcmp(op, "%")==0) return right != 0 ? left % right : 0;
    return 0;
}

void init_grid(){
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
            grid[i][j]='.';
    grid[player_x][player_y]=player_symbol;
}

void print_grid(){
    printf(YELLOW "Grid:\n");
    for(int i=0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++)
            printf("%c ", grid[i][j]);
        printf("\n");
    }
    printf(RESET);
}

void move_player(char *dir){
    int new_x = player_x, new_y = player_y;
    
    if(strcmp(dir,"UP")==0) new_x = (player_x-1+GRID_SIZE)%GRID_SIZE;
    if(strcmp(dir,"DOWN")==0) new_x = (player_x+1)%GRID_SIZE;
    if(strcmp(dir,"LEFT")==0) new_y = (player_y-1+GRID_SIZE)%GRID_SIZE;
    if(strcmp(dir,"RIGHT")==0) new_y = (player_y+1)%GRID_SIZE;
    
    char target = grid[new_x][new_y];
    
    // Check for different object types
    if(target == '#' || target == '|'){  // Obstacle or Wall
        printf(RED "Can't move! Obstacle in the way!\n" RESET);
        return;
    }
    
    if(target == 'D'){  // Door
        printf(RED "Door is locked! Need a key.\n" RESET);
        return;
    }
    
    if(target == '*'){  // Item
        player_score += 10;
        printf(GREEN "Collected item! Score: %d\n" RESET, player_score);
        play_sound();
    }
    
    if(target == '+'){  // Power-up
        player_score += 25;
        change_health(15);
        printf(GREEN "Power-up collected! Score: %d\n" RESET, player_score);
    }
    
    if(target == 'E'){  // Enemy
        change_health(-20);
        printf(RED "Enemy attacked you!\n" RESET);
        if(player_health > 0){
            grid[new_x][new_y] = '.';
            enemies_count--;
            printf(GREEN "Enemy defeated in combat!\n" RESET);
        }
    }
    
    if(target == 'T'){  // Teleport point
        printf(YELLOW "Stepped on teleport point\n" RESET);
    }
    
    // Move player
    grid[player_x][player_y] = '.';
    player_x = new_x;
    player_y = new_y;
    grid[player_x][player_y] = player_symbol;
    game_time++;
    
    // Check mission progress
    if(task_count > 0) check_mission_progress();
    
    print_grid();
    
    // Random events with adaptive probability
    int event_chance = adaptive_difficulty ? (5 + player_skill_level) : 5;
    if(generate_random(1, 100) <= event_chance){  
        printf(YELLOW "Random event: Found a potion!\n" RESET);
        add_to_inventory("potion");
    }
}

void place_object(char *type, int x, int y){
    if(x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE){
        printf(RED "Invalid position (%d, %d)!\n" RESET, x, y);
        return;
    }
    if(x == player_x && y == player_y){
        printf(RED "Can't place object on player!\n" RESET);
        return;
    }
    
    if(strcmp(type, "OBSTACLE") == 0){
        grid[x][y] = '#';
        printf(GREEN "Placed obstacle at (%d, %d)\n" RESET, x, y);
    } else if(strcmp(type, "ITEM") == 0){
        grid[x][y] = '*';
        printf(GREEN "Placed item at (%d, %d)\n" RESET, x, y);
    } else if(strcmp(type, "ENEMY") == 0){
        grid[x][y] = 'E';
        enemies_count++;
        printf(GREEN "Placed enemy at (%d, %d)\n" RESET, x, y);
    } else if(strcmp(type, "POWERUP") == 0){
        grid[x][y] = '+';
        printf(GREEN "Placed power-up at (%d, %d)\n" RESET, x, y);
    } else if(strcmp(type, "WALL") == 0){
        grid[x][y] = '|';
        printf(GREEN "Placed wall at (%d, %d)\n" RESET, x, y);
    } else if(strcmp(type, "DOOR") == 0){
        grid[x][y] = 'D';
        printf(GREEN "Placed door at (%d, %d)\n" RESET, x, y);
    }
    print_grid();
}

void set_grid_size(int size){
    // Validate grid size
    if(size != 3 && size != 4 && size != 5 && size != 10 && size != 15 && 
       size != 20 && size != 25 && size != 50 && size != 100){
        printf(RED "Invalid grid size! Choose from: 3, 4, 5, 10, 15, 20, 25, 50, 100\n" RESET);
        return;
    }
    
    if(size > MAX_GRID_SIZE){
        printf(RED "Grid size exceeds maximum (%d)!\n" RESET, MAX_GRID_SIZE);
        return;
    }
    
    GRID_SIZE = size;
    player_x = 0;
    player_y = 0;
    player_score = 0;
    player_health = max_health;
    game_time = 0;
    inventory_count = 0;
    teleport_count = 0;
    enemies_count = 0;
    init_grid();
    printf(GREEN "Grid size set to %dx%d. Game state reset!\n" RESET, size, size);
    print_grid();
}

void yyerror(const char *s){
    fprintf(stderr, RED "Error: %s\n" RESET, s);
}

// ---------------------- Main Program ----------------------

int main(int argc, char *argv[]){
    srand(time(NULL));  // Initialize random seed
    init_grid();
    while(1){
        printf("====================================\n");
        printf("  Mini Game Script Interpreter\n");
        printf("====================================\n");
        printf("Current Grid Size: %dx%d | Health: %d/%d\n", GRID_SIZE, GRID_SIZE, player_health, max_health);
        printf("1. Interactive Mode\n2. Run Script from File\n3. Change Grid Size\n4. Exit\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d",&choice);
        getchar(); // consume newline
        if(choice==1){
            interactive_mode=1;
            exit_interactive=0;
            // Reset game state for new session
            player_x = 0;
            player_y = 0;
            player_score = 0;
            player_health = max_health;
            game_time = 0;
            inventory_count = 0;
            teleport_count = 0;
            enemies_count = 0;
            var_count = 0;
            init_grid();
            
            printf(GREEN "\nInteractive Mode: Type commands (EXIT to quit)\n" RESET);
            printf("Available commands: MOVE, SAY, SET, ADD, SUBTRACT, IF, REPEAT, PLACE,\n");
            printf("                   GRIDSIZE, HEALTH, INVENTORY, USE, RANDOM, SOUND,\n");
            printf("                   WAIT, TELEPORT, STATUS, ATTACK, EXIT\n");
            printf("For multi-line blocks (REPEAT/IF), type commands until ENDREPEAT/ENDIF\n\n");
            print_grid();
            
            char buffer[4096];
            while(!exit_interactive){
                printf("> ");
                char line[256];
                if(!fgets(line,sizeof(line),stdin)) break;
                // Skip empty lines
                if(line[0] == '\n') continue;
                
                // Check if this starts a multi-line block
                int is_repeat = (strstr(line, "REPEAT") != NULL && strstr(line, "ENDREPEAT") == NULL);
                int is_if = (strstr(line, "IF") != NULL && strstr(line, "ENDIF") == NULL && strstr(line, "ENDIF") == NULL);
                
                if(is_repeat || is_if){
                    // Multi-line mode: accumulate lines until we find the closing keyword
                    strcpy(buffer, line);
                    int depth = 1;
                    char *start_keyword = is_repeat ? "REPEAT" : "IF";
                    char *end_keyword = is_repeat ? "ENDREPEAT" : "ENDIF";
                    
                    while(depth > 0 && !exit_interactive){
                        printf("... ");
                        char continuation[256];
                        if(!fgets(continuation,sizeof(continuation),stdin)) break;
                        if(continuation[0] == '\n') continue;
                        
                        // Check for nested blocks (only count if it's the same type and not the end)
                        if(is_repeat && strstr(continuation, "REPEAT") != NULL && strstr(continuation, "ENDREPEAT") == NULL) {
                            depth++;
                        } else if(is_if && strstr(continuation, "IF") != NULL && strstr(continuation, "ENDIF") == NULL) {
                            depth++;
                        }
                        
                        // Check for end keyword
                        if(strstr(continuation, end_keyword) != NULL) {
                            depth--;
                        }
                        
                        strcat(buffer, continuation);
                        
                        if(depth == 0) break;
                    }
                    
                    // Special handling for REPEAT blocks
                    if(is_repeat){
                        // Extract the repeat count and body
                        char *repeat_line = buffer;
                        int repeat_times = 0;
                        char body[4096] = "";
                        
                        // Parse "REPEAT n"
                        char *first_newline = strchr(repeat_line, '\n');
                        if(first_newline){
                            sscanf(repeat_line, "REPEAT %d", &repeat_times);
                            
                            // Extract body (everything between REPEAT line and ENDREPEAT)
                            char *body_start = first_newline + 1;
                            char *endrepeat_pos = strstr(body_start, "ENDREPEAT");
                            if(endrepeat_pos){
                                int body_len = endrepeat_pos - body_start;
                                strncpy(body, body_start, body_len);
                                body[body_len] = '\0';
                                
                                // Execute the body repeat_times times
                                for(int i = 0; i < repeat_times; i++){
                                    FILE *tmp = fmemopen(body, strlen(body), "r");
                                    if(tmp){
                                        yyin=tmp;
                                        yyparse();
                                        fclose(tmp);
                                    }
                                }
                            }
                        }
                    } else {
                        // Parse IF block normally
                        FILE *tmp = fmemopen(buffer, strlen(buffer), "r");
                        if(tmp){
                            yyin=tmp;
                            yyparse();
                            fclose(tmp);
                        }
                    }
                } else {
                    // Single line command
                    FILE *tmp = fmemopen(line, strlen(line), "r");
                    if(tmp){
                        yyin=tmp;
                        yyparse();
                        fclose(tmp);
                    }
                }
            }
            interactive_mode=0;
            printf(GREEN "\nExiting interactive mode...\n\n" RESET);
        } else if(choice==2){
            // Reset game state for new script
            player_x = 0;
            player_y = 0;
            player_score = 0;
            player_health = max_health;
            game_time = 0;
            inventory_count = 0;
            teleport_count = 0;
            enemies_count = 0;
            var_count = 0;
            init_grid();
            
            char filename[100];
            printf("Enter script filename: ");
            scanf("%s",filename);
            FILE *f = fopen(filename,"r");
            if(!f){ fprintf(stderr, RED "File not found!\n" RESET); continue; }
            
            printf(GREEN "\nRunning script: %s\n\n" RESET, filename);
            yyin=f;
            while(!feof(f)){
                yyparse();
            }
            fclose(f);
            printf(GREEN "\nScript execution completed.\n" RESET);
        } else if(choice==3){
            printf("\nAvailable grid sizes: 3, 4, 5, 10, 15, 20, 25, 50, 100\n");
            printf("Enter grid size: ");
            int new_size;
            scanf("%d", &new_size);
            getchar(); // consume newline
            set_grid_size(new_size);
            printf("\nPress Enter to continue...");
            getchar();
        } else break;
    }
    return 0;
}

// ---------------------- Mission Generation Functions ----------------------

void generate_mission(char *theme, int complexity){
    printf(GREEN "Generating %s mission with complexity %d...\n" RESET, theme, complexity);
    
    task_count = 0;
    current_mission_step = 0;
    strcpy(mission_theme, theme);
    
    // Simple mission generation based on theme
    if(strcmp(theme, "adventure") == 0){
        // Create tutorial task
        strcpy(mission_tasks[task_count].type, "tutorial");
        strcpy(mission_tasks[task_count].name, "start_quest");
        mission_tasks[task_count].x = generate_random(1, GRID_SIZE-2);
        mission_tasks[task_count].y = generate_random(1, GRID_SIZE-2);
        mission_tasks[task_count].required_task = -1;
        mission_tasks[task_count].completed = 0;
        task_count++;
        
        // Create challenge tasks
        for(int i = 0; i < complexity; i++){
            strcpy(mission_tasks[task_count].type, "challenge");
            sprintf(mission_tasks[task_count].name, "task_%d", i+1);
            mission_tasks[task_count].x = generate_random(1, GRID_SIZE-2);
            mission_tasks[task_count].y = generate_random(1, GRID_SIZE-2);
            mission_tasks[task_count].required_task = (i == 0) ? 0 : task_count - 1;
            mission_tasks[task_count].completed = 0;
            task_count++;
        }
        
        // Create final boss
        strcpy(mission_tasks[task_count].type, "boss");
        strcpy(mission_tasks[task_count].name, "final_boss");
        mission_tasks[task_count].x = generate_random(1, GRID_SIZE-2);
        mission_tasks[task_count].y = generate_random(1, GRID_SIZE-2);
        mission_tasks[task_count].required_task = task_count - 1;
        mission_tasks[task_count].completed = 0;
        task_count++;
    }
    
    place_mission_objects();
    printf(GREEN "Mission generated with %d tasks!\n" RESET, task_count);
    show_mission_status();
}

void generate_dungeon_space(int size, char *style){
    printf(GREEN "Generating %dx%d dungeon...\n" RESET, size, size);
    set_grid_size(size);
    
    // Create hub-and-spoke layout
    int center_x = size / 2;
    int center_y = size / 2;
    
    // Place central hub
    place_object("POWERUP", center_x, center_y);
    
    // Create four spokes
    if(center_x - 2 >= 0) place_object("ITEM", center_x - 2, center_y);
    if(center_x + 2 < size) place_object("ITEM", center_x + 2, center_y);
    if(center_y - 2 >= 0) place_object("ITEM", center_x, center_y - 2);
    if(center_y + 2 < size) place_object("ITEM", center_x, center_y + 2);
    
    printf(GREEN "Dungeon space generated!\n" RESET);
}

void place_mission_objects(){
    for(int i = 0; i < task_count; i++){
        int x = mission_tasks[i].x;
        int y = mission_tasks[i].y;
        
        // Ensure position is valid and not occupied
        if(x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && 
           grid[x][y] == '.' && (x != player_x || y != player_y)){
            
            if(strcmp(mission_tasks[i].type, "boss") == 0){
                grid[x][y] = 'B';
            } else if(strcmp(mission_tasks[i].type, "challenge") == 0){
                place_object("ENEMY", x, y);
            } else {
                grid[x][y] = 'M';  // Mission marker
            }
        }
    }
    print_grid();
}

void check_mission_progress(){
    for(int i = 0; i < task_count; i++){
        if(!mission_tasks[i].completed && 
           player_x == mission_tasks[i].x && player_y == mission_tasks[i].y){
            
            // Check if prerequisites are met
            if(mission_tasks[i].required_task == -1 || 
               mission_tasks[mission_tasks[i].required_task].completed){
                complete_task(i);
            } else {
                printf(YELLOW "Complete previous task first!\n" RESET);
            }
        }
    }
}

void complete_task(int task_id){
    if(task_id >= 0 && task_id < task_count && !mission_tasks[task_id].completed){
        mission_tasks[task_id].completed = 1;
        current_mission_step++;
        
        printf(GREEN "Task completed: %s\n" RESET, mission_tasks[task_id].name);
        play_sound();
        
        // Clear mission marker from grid
        grid[mission_tasks[task_id].x][mission_tasks[task_id].y] = '.';
        
        // Give rewards based on task type
        if(strcmp(mission_tasks[task_id].type, "boss") == 0){
            player_score += 500;
            printf(GREEN "MISSION COMPLETE!\n" RESET);
        } else if(strcmp(mission_tasks[task_id].type, "challenge") == 0){
            player_score += 100;
        } else {
            player_score += 50;
        }
        
        if(adaptive_difficulty) adapt_difficulty();
        print_grid();
    }
}

int find_task_by_name(char *name){
    for(int i = 0; i < task_count; i++){
        if(strcmp(mission_tasks[i].name, name) == 0){
            return i;
        }
    }
    printf(RED "Task '%s' not found\n" RESET, name);
    return -1;
}

void adapt_difficulty(){
    float success_rate = (game_time > 0) ? (float)current_mission_step / game_time : 0;
    
    if(success_rate > 0.8 && player_skill_level < 5){
        player_skill_level++;
        printf(YELLOW "Difficulty increased! Skill level: %d\n" RESET, player_skill_level);
    } else if(success_rate < 0.3 && player_skill_level > 1){
        player_skill_level--;
        printf(YELLOW "Difficulty decreased! Here's some help. Skill level: %d\n" RESET, player_skill_level);
        change_health(25);  // Give health boost
    }
}

void show_mission_status(){
    if(task_count == 0){
        printf(YELLOW "No active mission\n" RESET);
        return;
    }
    
    printf(YELLOW "\n=== Mission Status ===\n" RESET);
    printf("Theme: %s | Progress: %d/%d tasks\n", mission_theme, current_mission_step, task_count);
    printf("Skill Level: %d | Adaptive: %s\n", player_skill_level, adaptive_difficulty ? "ON" : "OFF");
    
    for(int i = 0; i < task_count; i++){
        char status_icon;
        if(mission_tasks[i].completed){
            status_icon = 'X';
        } else if(mission_tasks[i].required_task == -1 || 
                  mission_tasks[mission_tasks[i].required_task].completed){
            status_icon = 'O';  // Available
        } else {
            status_icon = '-';  // Blocked
        }
        
        printf("%c %s (%s) at (%d,%d)\n", 
               status_icon, mission_tasks[i].name, mission_tasks[i].type,
               mission_tasks[i].x, mission_tasks[i].y);
    }
    printf(RESET);
}

void procedural_populate(int density, char *type){
    printf(GREEN "Procedurally populating with %d %s objects...\n" RESET, density, type);
    
    int placed = 0;
    int attempts = 0;
    int max_attempts = density * 3;
    
    while(placed < density && attempts < max_attempts){
        int x = generate_random(1, GRID_SIZE-2);
        int y = generate_random(1, GRID_SIZE-2);
        
        // Only place if cell is empty and not player position
        if(grid[x][y] == '.' && (x != player_x || y != player_y)){
            if(strcmp(type, "random") == 0){
                // Random object selection
                int obj_type = generate_random(1, 6);
                switch(obj_type){
                    case 1: place_object("OBSTACLE", x, y); break;
                    case 2: place_object("ITEM", x, y); break;
                    case 3: place_object("ENEMY", x, y); break;
                    case 4: place_object("POWERUP", x, y); break;
                    case 5: place_object("WALL", x, y); break;
                    case 6: place_object("DOOR", x, y); break;
                }
            } else {
                place_object(type, x, y);
            }
            placed++;
        }
        attempts++;
    }
    
    printf(GREEN "Placed %d objects (%d attempts)\n" RESET, placed, attempts);
}
