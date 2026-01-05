/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "script.y"

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


#line 188 "script.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "script.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MOVE = 3,                       /* MOVE  */
  YYSYMBOL_SAY = 4,                        /* SAY  */
  YYSYMBOL_SET = 5,                        /* SET  */
  YYSYMBOL_ADD = 6,                        /* ADD  */
  YYSYMBOL_SUBTRACT = 7,                   /* SUBTRACT  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ENDIF = 9,                      /* ENDIF  */
  YYSYMBOL_EXIT = 10,                      /* EXIT  */
  YYSYMBOL_IDENTIFIER = 11,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 12,                    /* STRING  */
  YYSYMBOL_DIRECTION = 13,                 /* DIRECTION  */
  YYSYMBOL_OPERATOR = 14,                  /* OPERATOR  */
  YYSYMBOL_REPEAT = 15,                    /* REPEAT  */
  YYSYMBOL_ENDREPEAT = 16,                 /* ENDREPEAT  */
  YYSYMBOL_PLACE = 17,                     /* PLACE  */
  YYSYMBOL_OBJECT_TYPE = 18,               /* OBJECT_TYPE  */
  YYSYMBOL_ARITHOP = 19,                   /* ARITHOP  */
  YYSYMBOL_GRIDSIZE = 20,                  /* GRIDSIZE  */
  YYSYMBOL_HEALTH = 21,                    /* HEALTH  */
  YYSYMBOL_INVENTORY = 22,                 /* INVENTORY  */
  YYSYMBOL_USE = 23,                       /* USE  */
  YYSYMBOL_RANDOM = 24,                    /* RANDOM  */
  YYSYMBOL_SOUND = 25,                     /* SOUND  */
  YYSYMBOL_WAIT = 26,                      /* WAIT  */
  YYSYMBOL_TELEPORT = 27,                  /* TELEPORT  */
  YYSYMBOL_STATUS = 28,                    /* STATUS  */
  YYSYMBOL_ATTACK = 29,                    /* ATTACK  */
  YYSYMBOL_MISSION = 30,                   /* MISSION  */
  YYSYMBOL_GENERATE = 31,                  /* GENERATE  */
  YYSYMBOL_THEME = 32,                     /* THEME  */
  YYSYMBOL_COMPLETE = 33,                  /* COMPLETE  */
  YYSYMBOL_ADAPT = 34,                     /* ADAPT  */
  YYSYMBOL_POPULATE = 35,                  /* POPULATE  */
  YYSYMBOL_NUMBER = 36,                    /* NUMBER  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_script = 40,                    /* script  */
  YYSYMBOL_commands = 41,                  /* commands  */
  YYSYMBOL_expr = 42,                      /* expr  */
  YYSYMBOL_command = 43                    /* command  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  5
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  76

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   133,   133,   136,   138,   142,   143,   144,   145,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   172,   180,   182
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MOVE", "SAY", "SET",
  "ADD", "SUBTRACT", "IF", "ENDIF", "EXIT", "IDENTIFIER", "STRING",
  "DIRECTION", "OPERATOR", "REPEAT", "ENDREPEAT", "PLACE", "OBJECT_TYPE",
  "ARITHOP", "GRIDSIZE", "HEALTH", "INVENTORY", "USE", "RANDOM", "SOUND",
  "WAIT", "TELEPORT", "STATUS", "ATTACK", "MISSION", "GENERATE", "THEME",
  "COMPLETE", "ADAPT", "POPULATE", "NUMBER", "'('", "')'", "$accept",
  "script", "commands", "expr", "command", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-36)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -36,     8,   114,   -36,    -2,    -1,     1,     3,     4,     5,
     -36,    -7,     7,    -7,    -7,     6,    10,    11,    -7,    -7,
      12,   -36,   -36,     9,    22,    24,    -7,    26,   -36,    25,
     -36,    -7,    -7,    -7,    28,   -36,   -36,    -7,    21,    23,
      21,    21,   -36,   -36,    -7,    21,    21,    -7,    32,    -7,
     -36,    21,    -7,   -36,    21,    21,    21,    -7,   -12,    -7,
      48,    30,    -9,    -9,   -36,    21,    21,    21,   -36,   -36,
     -36,   -36,    21,    21,    81,   -36
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,    24,     0,     0,     0,     0,     0,     4,     0,
      10,     0,     0,     0,     0,     6,     5,     0,     3,     0,
      14,    15,    16,    17,     0,    19,    20,    22,     0,     0,
      27,    28,     0,     9,    11,    12,    13,     0,     0,     0,
       0,     0,     0,     0,    25,    26,    29,     3,     8,     7,
      31,    32,    18,    21,     0,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -35,   -13,   -36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    38,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    41,    35,    60,    35,    45,    46,    59,     3,    29,
      59,    30,    31,    51,    32,    33,    34,    42,    54,    55,
      56,    43,    44,    47,    58,    39,    68,    36,    37,    36,
      37,    62,    74,    49,    63,    50,    65,    52,    53,    66,
      59,    48,    57,    64,    67,     0,    69,     0,     0,    72,
      73,     4,     5,     6,     7,     8,     9,     0,    10,    61,
       0,     0,     0,    11,    70,    12,    71,     0,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,    25,    26,    27,     4,     5,     6,     7,     8,     9,
      75,    10,     0,     0,     0,     0,    11,     0,    12,     0,
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,    25,    26,    27,     4,     5,     6,
       7,     8,     9,     0,    10,     0,     0,     0,     0,    11,
       0,    12,     0,     0,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,    25,    26,    27
};

static const yytype_int8 yycheck[] =
{
      13,    14,    11,    38,    11,    18,    19,    19,     0,    11,
      19,    12,    11,    26,    11,    11,    11,    11,    31,    32,
      33,    11,    11,    11,    37,    18,    38,    36,    37,    36,
      37,    44,    67,    11,    47,    11,    49,    11,    13,    52,
      19,    32,    14,    11,    57,    -1,    59,    -1,    -1,    62,
      63,     3,     4,     5,     6,     7,     8,    -1,    10,    36,
      -1,    -1,    -1,    15,    16,    17,    36,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    34,    35,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    15,    -1,    17,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    35,     3,     4,     5,
       6,     7,     8,    -1,    10,    -1,    -1,    -1,    -1,    15,
      -1,    17,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,     0,     3,     4,     5,     6,     7,     8,
      10,    15,    17,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    33,    34,    35,    43,    11,
      12,    11,    11,    11,    11,    11,    36,    37,    42,    18,
      42,    42,    11,    11,    11,    42,    42,    11,    32,    11,
      11,    42,    11,    13,    42,    42,    42,    14,    42,    19,
      41,    36,    42,    42,    11,    42,    42,    42,    38,    42,
      16,    36,    42,    42,    41,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     3,     3,     3,
       2,     3,     3,     3,     2,     2,     2,     2,     4,     2,
       2,     4,     2,     1,     1,     3,     3,     2,     2,     3,
       6,     4,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* expr: NUMBER  */
#line 142 "script.y"
                                    { (yyval.num) = (yyvsp[0].num); }
#line 1271 "script.tab.c"
    break;

  case 6: /* expr: IDENTIFIER  */
#line 143 "script.y"
                                    { (yyval.num) = get_var((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1277 "script.tab.c"
    break;

  case 7: /* expr: expr ARITHOP expr  */
#line 144 "script.y"
                                    { (yyval.num) = eval_arith((yyvsp[-2].num), (yyvsp[-1].str), (yyvsp[0].num)); }
#line 1283 "script.tab.c"
    break;

  case 8: /* expr: '(' expr ')'  */
#line 145 "script.y"
                                    { (yyval.num) = (yyvsp[-1].num); }
#line 1289 "script.tab.c"
    break;

  case 9: /* command: MOVE IDENTIFIER DIRECTION  */
#line 149 "script.y"
                                    { move_player((yyvsp[0].str)); }
#line 1295 "script.tab.c"
    break;

  case 10: /* command: SAY STRING  */
#line 150 "script.y"
                                   { printf(GREEN "%s\n" RESET, (yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1301 "script.tab.c"
    break;

  case 11: /* command: SET IDENTIFIER expr  */
#line 151 "script.y"
                                   { set_var((yyvsp[-1].str), (yyvsp[0].num)); printf(GREEN "%s set to %d\n" RESET, (yyvsp[-1].str), (yyvsp[0].num)); free((yyvsp[-1].str)); }
#line 1307 "script.tab.c"
    break;

  case 12: /* command: ADD IDENTIFIER expr  */
#line 152 "script.y"
                                   { add_var((yyvsp[-1].str), (yyvsp[0].num)); printf(GREEN "%s updated to %d\n" RESET, (yyvsp[-1].str), get_var((yyvsp[-1].str))); free((yyvsp[-1].str)); }
#line 1313 "script.tab.c"
    break;

  case 13: /* command: SUBTRACT IDENTIFIER expr  */
#line 153 "script.y"
                                   { subtract_var((yyvsp[-1].str), (yyvsp[0].num)); printf(GREEN "%s updated to %d\n" RESET, (yyvsp[-1].str), get_var((yyvsp[-1].str))); free((yyvsp[-1].str)); }
#line 1319 "script.tab.c"
    break;

  case 14: /* command: GRIDSIZE expr  */
#line 154 "script.y"
                                   { set_grid_size((yyvsp[0].num)); }
#line 1325 "script.tab.c"
    break;

  case 15: /* command: HEALTH expr  */
#line 155 "script.y"
                                   { change_health((yyvsp[0].num)); }
#line 1331 "script.tab.c"
    break;

  case 16: /* command: INVENTORY IDENTIFIER  */
#line 156 "script.y"
                                   { add_to_inventory((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1337 "script.tab.c"
    break;

  case 17: /* command: USE IDENTIFIER  */
#line 157 "script.y"
                                   { use_item((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1343 "script.tab.c"
    break;

  case 18: /* command: RANDOM IDENTIFIER expr expr  */
#line 158 "script.y"
                                   { set_var((yyvsp[-2].str), generate_random((yyvsp[-1].num), (yyvsp[0].num))); free((yyvsp[-2].str)); }
#line 1349 "script.tab.c"
    break;

  case 19: /* command: SOUND expr  */
#line 159 "script.y"
                                   { sound_enabled = (yyvsp[0].num); printf(GREEN "Sound %s\n" RESET, (yyvsp[0].num) ? "enabled" : "disabled"); }
#line 1355 "script.tab.c"
    break;

  case 20: /* command: WAIT expr  */
#line 160 "script.y"
                                   { wait_time((yyvsp[0].num)); }
#line 1361 "script.tab.c"
    break;

  case 21: /* command: TELEPORT IDENTIFIER expr expr  */
#line 161 "script.y"
                                    { create_teleport((yyvsp[-2].str), (yyvsp[-1].num), (yyvsp[0].num)); free((yyvsp[-2].str)); }
#line 1367 "script.tab.c"
    break;

  case 22: /* command: TELEPORT IDENTIFIER  */
#line 162 "script.y"
                                   { teleport_to((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1373 "script.tab.c"
    break;

  case 23: /* command: STATUS  */
#line 163 "script.y"
                                   { show_status(); }
#line 1379 "script.tab.c"
    break;

  case 24: /* command: ATTACK  */
#line 164 "script.y"
                                   { attack_enemies_nearby(); }
#line 1385 "script.tab.c"
    break;

  case 25: /* command: MISSION THEME IDENTIFIER  */
#line 165 "script.y"
                                   { strcpy(mission_theme, (yyvsp[0].str)); generate_mission((yyvsp[0].str), dungeon_complexity); free((yyvsp[0].str)); }
#line 1391 "script.tab.c"
    break;

  case 26: /* command: GENERATE IDENTIFIER expr  */
#line 166 "script.y"
                                   { if(strcmp((yyvsp[-1].str), "dungeon") == 0) generate_dungeon_space((yyvsp[0].num), generation_style); free((yyvsp[-1].str)); }
#line 1397 "script.tab.c"
    break;

  case 27: /* command: COMPLETE IDENTIFIER  */
#line 167 "script.y"
                                   { int task_id = find_task_by_name((yyvsp[0].str)); if(task_id >= 0) complete_task(task_id); free((yyvsp[0].str)); }
#line 1403 "script.tab.c"
    break;

  case 28: /* command: ADAPT expr  */
#line 168 "script.y"
                                   { adaptive_difficulty = (yyvsp[0].num); if((yyvsp[0].num)) adapt_difficulty(); printf(GREEN "Adaptive difficulty %s\n" RESET, (yyvsp[0].num) ? "enabled" : "disabled"); }
#line 1409 "script.tab.c"
    break;

  case 29: /* command: POPULATE IDENTIFIER expr  */
#line 169 "script.y"
                                   { procedural_populate((yyvsp[0].num), (yyvsp[-1].str)); free((yyvsp[-1].str)); }
#line 1415 "script.tab.c"
    break;

  case 30: /* command: IF IDENTIFIER OPERATOR expr commands ENDIF  */
#line 171 "script.y"
        { if(eval_expr(get_var((yyvsp[-4].str)), (yyvsp[-3].str), (yyvsp[-2].num))) { /* already executed commands */ } }
#line 1421 "script.tab.c"
    break;

  case 31: /* command: REPEAT expr commands ENDREPEAT  */
#line 173 "script.y"
        { 
            // Note: This simple implementation executes loop body once during parsing
            // For proper loop execution, you'd need to store and re-execute the commands
            for(int i = 1; i < (yyvsp[-2].num); i++) {
                printf(YELLOW "Loop iteration %d\n" RESET, i+1);
            }
        }
#line 1433 "script.tab.c"
    break;

  case 32: /* command: PLACE OBJECT_TYPE NUMBER NUMBER  */
#line 181 "script.y"
        { place_object((yyvsp[-2].str), (yyvsp[-1].num), (yyvsp[0].num)); }
#line 1439 "script.tab.c"
    break;

  case 33: /* command: EXIT  */
#line 183 "script.y"
        { 
            if(interactive_mode) {
                exit_interactive = 1;
            } else {
                exit(0);
            }
        }
#line 1451 "script.tab.c"
    break;


#line 1455 "script.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 192 "script.y"


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
