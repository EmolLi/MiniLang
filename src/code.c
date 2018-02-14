#include <stdio.h>
#include <string.h>
#include "code.h"
#include "symbol.h"

FILE* output;
const char* filename;
int indentation;

void codeProgram(Node *n){
    codeInit();
    codeGenerate(n);
}

void codeInit(){
    indentation = 0;
    fprintf(output, "#include <stdio.h>\n");
    fprintf(output, "#include <stdlib.h>\n");
    fprintf(output, "#include <string.h>\n");
    nextLine();
    nextLine();
    nextLine();

    // helper functions
    const char* stringAdd =
        "char* StringAdd(char* str1, char* str2){\n"
        "	char* result = (char*)malloc((strlen(str1) + strlen(str2) + 2) * sizeof(char));\n"
        "	strcpy(result, str1);\n"
        "	strcat(result, str2);\n"
        "	return str;\n"
        "}\n";

    const char* stringMult =
        "char* StringMult(char* str, int times){\n"
        "   if (times == 0) return \"\";\n"
        "   if (times < 0) fprintf(stderr, \"Error: cannot multiple a string with a negative number.\\n\");"
        "	char* result = (char*)malloc((strlen(str) + 2) * times * sizeof(char));\n"
        "	strcpy(str, str1);\n"
        "	strcat(str, str2);\n"
        "	return str;\n"
        "}\n";

    nextLine();
    nextLine();
    fprintf(output, "int main(int argc, char **argv) {");
    indentation++;
    nextLine();
}

void codeGenerate(Node* n){
    if (n != NULL){
        switch (n->kind) {
            case k_NodeKindProg:
                codeGenerate(n->val.prog.declarations);
                codeGenerate(n->val.prog.statements);
                break;

            case k_NodeKindTypeInt:
                fprintf(output, "int");
                break;

            case k_NodeKindTypeBool:
                fprintf(output, "bool");
                break;

            case k_NodeKindTypeFloat:
                fprintf(output, "float");
                break;

            case k_NodeKindTypeString:
                fprintf(output, "char*");
                break;

            case k_NodeKindDeclaration:
                codeGenerate(val.declaration.varType);
                codeGenerate(n->val.declaration.ident);
                fprintf(output, " = ");
                codeGenerate(n->val.declaration.exp);
                nextLine();
                break;

            case k_NodeKindDeclarations:
                codeGenerate(n->val.declarations.declarations);
                codeGenerate(n->val.declarations.declaration);
                break;

            case k_NodeKindStatements:
                codeGenerate(n->val.statements.statements);
                codeGenerate(n->val.statements.statement);
                break;

            case k_NodeKindStatementRead:
                switch (n->type) {
                    case st_BOOL:
                    case st_INT:
                        fprintf(output, "scanf(\"%%d\", &");
                        break;
                    case st_FLOAT:
                        fprintf(output, "scanf(\"%%f\", &");
                        break;
                    case st_STRING:
                        fprintf(output, "scanf(\"%%s\", &");
                        break;
                }

                codeGenerate(n->val.node);
                fprintf(output,")");
                nextLine();
                break;

            case k_NodeKindStatementPrint:
                switch (n->type) {
                    case st_BOOL:
                    case st_INT:
                        fprintf(output, "printf(\"%%d\\n\", ");
                        break;
                    case st_FLOAT:
                        fprintf(output, "printf(\"%%f\\n\", ");
                        break;
                    case st_STRING:
                        fprintf(output, "printf(\"%%d\\n\", ");
                        break;
                }
                codeGenerate(n->val.node);
                fprintf(output,")");
                nextLine();
                break;

            case k_NodeKindStatementAssign:
                codeGenerate(n->val.assignStatement.ident);
                fprintf(output, " = ");
                codeGenerate(n->val.assignStatement.exp);
                nextLine();
                break;

            case k_NodeKindStatementIf:
                fprintf(output, "if (");
                codeGenerate(n->val.ifStatement.exp);
                fprintf(output, "){");
                indentation++;
                nextLine();
                codeGenerate(n->val.ifStatement.statements);
                fprintf(output, "} else { ");
                nextLine();
                codeGenerate(n->val.ifStatement.elseStatement);
                fprintf(output, "}");
                indentation--;
                nextLine();
                break;

            case k_NodeKindStatementElse:
                codeGenerate(n->val.node);
                nextLine();
                break;

            case k_NodeKindStatementWhile:
                fprintf(output, "while (");
                codeGenerate(n->val.whileStatement.exp);
                fprintf(output, "){");
                indentation++;
                nextLine();
                codeGenerate(n->val.whileStatement.statements);
                fprintf(output, "}");
                indentation--;
                nextLine();
                break;

            default:
                codeExp(n);
                break;
        }
    }
}

void codeExp(Node* exp){
    // typeData sv = exp->symbol->evalValue;
    switch (exp->kind) {
        case k_NodeKindExpIdentifier:
            fprintf(output, " %s\n", exp->val.identifier);
            break;

        case k_NodeKindExpIntLiteral:
            fprintf(output, " %d\n", exp->val.intLiteral);
            break;

        case k_NodeKindExpFloatLiteral:
            fprintf(output, " %f", exp->val.floatLiteral);
            break;

        case k_NodeKindExpStringLiteral:
            fprintf(output, " \"%s\"", exp->val.stringLiteral);
            break;

        case k_NodeKindExpBoolLiteral:
            fprintf(output, " %d", exp->val.boolLiteral);
            break;


        case k_NodeKindExpUMinus:
            fprintf(output, " (-");
            codeExp(exp->val.node);
            fprintf(")");
            break;

        case k_NodeKindExpNeg:
            fprintf(output, " (!");
            codeExp(exp->val.node);
            fprintf(")");
            break;

        default:
            codeBinaryExp(exp);
            break;


    }
}


void codeBinaryExp(Node* exp){
    Node* lhs = exp->val.binary.lhs;
    Node* rhs = exp->val.binary.rhs;
    // typeData sv = exp->symbol->evalValue;

    // evalExp(lhs);
    // evalExp(rhs);

    switch (exp->kind) {

        case k_NodeKindExpAddition:
            if (lhs->type == st_STRING && rhs->type == st_STRING){
                fprintf(output, " StringAdd(");
                codeExp(lhs);
                fprintf(output, ", ");
                codeExp(rhs);
                fprintf(output, ")");
                break;
            }
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " +");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        case k_NodeKindExpSubtraction:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " -");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        case k_NodeKindExpMultiplication:
            if (lhs->type == st_STRING && rhs->type == st_INT){
                fprintf(output, " StringMult(");
                codeExp(lhs);
                fprintf(output, ", ");
                codeExp(rhs);
                fprintf(output, ")");
                break;
            }
            if (rhs->type == st_STRING && lhs->type == st_INT){
                fprintf(output, " StringMult(");
                codeExp(rhs);
                fprintf(output, ", ");
                codeExp(lhs);
                fprintf(output, ")");
                break;
            }
            else{
                fprintf(output, " (");
                codeExp(lhs);
                fprintf(output, " *");
                codeExp(rhs);
                fprintf(output, " )");
            }
            break;

        case k_NodeKindExpDivision:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " /");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        case k_NodeKindExpEqual:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " ==");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        case k_NodeKindExpNotEqual:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " !=");
            codeExp(rhs);
            fprintf(output, " )");
            break;
            //FIXME: 1 && TRUE???

        case k_NodeKindExpAnd:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " &&");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        case k_NodeKindExpOr:
            fprintf(output, " (");
            codeExp(lhs);
            fprintf(output, " ||");
            codeExp(rhs);
            fprintf(output, " )");
            break;

        default:
            printf("ERROR code binary\n");
            exit(2);
    }
}


void indent(){
    for (int i = 0; i < indentation; i++){
        fprintf(output, "\t");
    }
}

void nextLine(){
    fprintf(";\n");
    indent();
}
