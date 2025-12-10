%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Function prototypes
int yylex();
void yyerror(const char *s);
int get_var(char *name);
void set_var(char *name, int value);
void add_var(char *name, int value);
void subtract_var(char *name, int value);
int eval_expr(int left, char *op, int right);
void init_grid();
void print_grid();
void move_player(char *dir);

int interactive_mode = 0;
FILE *script_file = NULL;

%}

%union {
    char* str;
    int num;
}

%token <str> MOVE SAY SET ADD SUBTRACT IF ENDIF EXIT IDENTIFIER STRING DIRECTION OPERATOR
%token <num> NUMBER

%%

script:
    commands
    ;

commands:
      /* empty */
    | commands command
    ;

command:
      MOVE IDENTIFIER DIRECTION     { move_player($3); }
    | SAY STRING                   { printf(GREEN "%s\n" RESET, $2); free($2); }
    | SET IDENTIFIER NUMBER         { set_var($2, $3); printf(GREEN "%s set to %d\n" RESET, $2, $3); free($2); }
    | ADD IDENTIFIER NUMBER         { add_var($2, $3); printf(GREEN "%s updated to %d\n" RESET, $2, get_var($2)); free($2); }
    | SUBTRACT IDENTIFIER NUMBER    { subtract_var($2, $3); printf(GREEN "%s updated to %d\n" RESET, $2, get_var($2)); free($2); }
    | IF IDENTIFIER OPERATOR NUMBER commands ENDIF
        { if(eval_expr(get_var($2), $3, $4)) { /* already executed commands */ } }
    | EXIT
        { exit(0); }
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
    grid[player_x][player_y]='.';
    if(strcmp(dir,"UP")==0) player_x = (player_x-1+GRID_SIZE)%GRID_SIZE;
    if(strcmp(dir,"DOWN")==0) player_x = (player_x+1)%GRID_SIZE;
    if(strcmp(dir,"LEFT")==0) player_y = (player_y-1+GRID_SIZE)%GRID_SIZE;
    if(strcmp(dir,"RIGHT")==0) player_y = (player_y+1)%GRID_SIZE;
    grid[player_x][player_y]=player_symbol;
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
            printf("Interactive Mode: Type commands (EXIT to quit)\n");
            while(1){
                printf("> ");
                char line[256];
                if(!fgets(line,sizeof(line),stdin)) break;
                FILE *tmp = fmemopen(line, strlen(line), "r");
                if(tmp){
                    yyin=tmp;
                    yyparse();
                    fclose(tmp);
                }
            }
        } else if(choice==2){
            char filename[100];
            printf("Enter script filename: ");
            scanf("%s",filename);
            FILE *f = fopen(filename,"r");
            if(!f){ fprintf(stderr, RED "File not found!\n" RESET); continue; }
            yyin=f;
            while(!feof(f)){
                yyparse();
            }
            fclose(f);
        } else break;
    }
    return 0;
}
