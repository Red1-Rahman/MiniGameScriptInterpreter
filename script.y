%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;

#define GRID_SIZE 10

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

// Player position
int player_x = 0, player_y = 0;
char player_symbol = 'P';
char grid[GRID_SIZE][GRID_SIZE];

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

%token <str> MOVE SAY SET ADD SUBTRACT IF ENDIF EXIT IDENTIFIER STRING DIRECTION OPERATOR REPEAT ENDREPEAT PLACE OBJECT_TYPE ARITHOP
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

// ---------------------- Helper Functions ----------------------

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
    
    // Check for obstacles
    if(grid[new_x][new_y] == '#'){
        printf(RED "Can't move! Obstacle in the way!\n" RESET);
        return;
    }
    
    // Check for items
    if(grid[new_x][new_y] == '*'){
        player_score += 10;
        printf(GREEN "Collected item! Score: %d\n" RESET, player_score);
    }
    
    grid[player_x][player_y]='.';
    player_x = new_x;
    player_y = new_y;
    grid[player_x][player_y]=player_symbol;
    print_grid();
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
    }
    print_grid();
}

void yyerror(const char *s){
    fprintf(stderr, RED "Error: %s\n" RESET, s);
}

// ---------------------- Main Program ----------------------

int main(int argc, char *argv[]){
    init_grid();
    while(1){
        printf("====================================\n");
        printf("  Mini Game Script Interpreter\n");
        printf("====================================\n");
        printf("1. Interactive Mode\n2. Run Script from File\n3. Exit\n");
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
            var_count = 0;
            init_grid();
            
            printf(GREEN "\nInteractive Mode: Type commands (EXIT to quit)\n" RESET);
            printf("Available commands: MOVE, SAY, SET, ADD, SUBTRACT, IF, REPEAT, PLACE, EXIT\n");
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
        } else break;
    }
    return 0;
}
