#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.c"

struct Context
{
    size_t numNames;
    char **names;
    char **definitions;
};

static struct Context context = {
        .numNames = 0,
};

void initContext()
{
    context.names = malloc(100 * sizeof(char *));
    context.definitions = malloc(100 * sizeof(char *));
}

void set(char *expr)
{
    char name[100];
    char trans[100];
    printf("%s ", expr);

    sscanf(expr, "%99[^,]", name);
    sscanf(expr, "%*[^,]%99[^\n]", trans);
    context.names[context.numNames] = strdup(name);
    printf("%s ", name);

    printf("%s ", context.names[context.numNames]);

    if (context.names[context.numNames] != NULL)
    {
        context.numNames++;
    }
    else
    {
        printf("Memory allocation error\n");
    }
}

// struct Expression *
// struct Expression *parseExpression(char **expr)
// {

//     char name[50];

//     sscanf(*expr, "%49[^[,]]", name);
//     // sscanf(*expr, "%*[^[][%[^,], %[^]]]", arg1, arg2);
//     // printf("%s %s", arg1, arg2);
//     (*expr)++;
//     Expression *node = createNode(name);

//     while (**expr != ',' && **expr != ']')
//     {

//         addChild(node, parseExpression(expr));

//         // met , go up - how to go up??

//         // create expression and every other expression inside the [ ] mark as a child expression
//         // comma decides how many child expressions one has
//     }
//     if (**expr == ',')
//     {
//         (*expr)++;
//     }

// addSibling(node, parseExpression(expr));

// if (**expr == '[')
// {

//     addChild();

//     if (**expr == ',')
//     {
//         (*expr)++;
//     }
//     functionNode->right = parsePrimary(expr);

//     if (**expr == ']')
//     {
//         (*expr)++;
//     }
//     else
//     {
//         fprintf(stderr, "Error: Mismatched parentheses\n");
//         exit(EXIT_FAILURE);
//     }
// }
// if (!strcmp(name, "set"))
// {
//     context.names[context.numNames] = strdup(arg1);
//     context.definitions[context.numNames] = strdup(arg2);
//     printf("%s ", context.names[context.numNames]);

//     context.numNames++;
// }
// if (!strcmp(name, "sum"))
// {
//     context.names[context.numNames] = strdup(arg1);
//     context.definitions[context.numNames] = strdup(arg2);
//     context.numNames++;
// }

// for (int i = 0; i < 100; ++i)
// {
//     if (names.getIndex(name) == null ) {
//         leave name as it is
//     } else {
//         expression.replace(definiton[i]);
//     }
// }


struct Expression *parseExpression(char **expr)
{
    char name[50] = {};

    printf("%c ", **expr);

    if (sscanf(*expr, "%49[^],[]", name) != 1) { // Error here
        return NULL;
    }

    (*expr) += strlen(name);
    Expression *node = createNode(name);
    (*expr)++;

    while (**expr != ',' && **expr != ']')
    {
        addChild(node, parseExpression(expr));
    }


//    if (**expr == ',')
//    {
//        (*expr)++;
//    }
//    if (**expr == '\0' || **expr == ' ' ||  **expr == ';') {
//        return node;
//    }

    return node;
}

// struct ExpressionNode *parseArguments(char **expr, Function func)
// {
//     func.numArguments = 0;
//     func.arguments = malloc(50 * sizeof(Variable));
//     while (*expr != ')')
//     {
//         expr++;
//         func.arguments[func.numArguments].type = null;

//         ExpressionNode *argExpression = parseExpression(&mutableInput);
//         if (argExpression->type == VARIABLE)
//         {
//             strcpy(func.arguments[func.numArguments].name, argExpression->variable->name);
//         }
//         if (argExpression->type == CONSTANT)
//         {
//             strcpy(func.arguments[func.numArguments].name, argExpression->variable->name);
//         }
//     }
// }
