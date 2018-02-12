#include <stdio.h>
#include "pretty.h"

void prettyNode(Node *e)
{
    if (e == null) return;

	switch (e->kind) {
        case k_NodeKindExpIdentifier:
			printf("%s", e->val.identifier);
			break;

        case k_NodeKindExpIntLiteral:
			printf("%i", e->val.intLiteral);
			break;

        case k_NodeKindExpFloatLiteral:
            printf("%f", e->val.floatLiteral);
            break;

        case k_NodeKindExpStringLiteral:
            printf("%s", e->val.stringLiteral);
            break;

        case k_NodeKindExpBoolLiteral:
            printf(e->val.boolLiteral ? "TRUE" : "FALSE");

		case k_NodeKindExpAddition:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("+");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

		case k_NodeKindExpSubtraction:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("-");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

		case k_NodeKindExpMultiplication:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("*");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

		case k_NodeKindExpDivision:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("/");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

        case k_NodeKindExpEqual:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("==");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

        case k_NodeKindExpNotEqual:
			printf("(");
			prettyNode(e->val.binary.lhs);
			printf("!=");
			prettyNode(e->val.binary.rhs);
			printf(")");
			break;

        case k_NodeKindExpAnd:
            printf("(");
            prettyNode(e->val.binary.lhs);
            printf("&&");
            prettyNode(e->val.binary.rhs);
            printf(")");
            break;

        case k_NodeKindExpOr:
            printf("(");
            prettyNode(e->val.binary.lhs);
            printf("||");
            prettyNode(e->val.binary.rhs);
            printf(")");
            break;

        case k_NodeKindExpUMinus:
            printf("(-");
            prettyNode(e->val.node);
            printf(")");
            break;

        case k_NodeKindExpNeg:
            printf("(!");
            prettyNode(e->val.node);
            printf(")");
            break;

        case k_NodeKindTypeInt:
            printf("int");
            break;

        case k_NodeKindTypeBool:
            printf("boolean");
            break;

        case k_NodeKindTypeFloat:
            printf("float");
            break;

        case k_NodeKindTypeString:
            printf("string");
            break;

        case k_NodeKindDeclaration:
            printf("var %s : ", e->val.declaration.ident);
            prettyNode(e->val.declaration.varType);
            printf(" = ");
            prettyNode(e->val.declaration.exp);
            printf(";\n");
            break;

        case k_NodeKindDeclarations:
            prettyNode(e->val.declarations.declarations);
            prettyNode(e->val.declarations.declaration);
            break;

        case k_NodeKindStatements:
            prettyNode(e->val.statements.statements);
            prettyNode(e->val.statements.statement);
            break;

        case k_NodeKindStatementRead:
            printf("read ");
            prettyNode(e->val.node);
            printf(";\n");
            break;

        case k_NodeKindStatementPrint:
            printf("print ");
            prettyNode(e->val.node);
            printf(";\n");
            break;

        case k_NodeKindStatementAssign:
            prettyNode(e->val.assignStatement.ident);
            printf(" = ");
            prettyNode(e->val.assignStatement.exp);
            printf(";\n");
            break;

        case k_NodeKindStatementIf:
            printf("if ");
            prettyNode(e->val.ifStatement.exp);
            printf("\n{ \n");
            prettyNode(e->val.ifStatement.statements);
            printf("} else { \n");
            prettyNode(e->val.ifStatement.elseStatement);
            printf("}\n");
            break;


        case k_NodeKindStatementElse:
            prettyNode(e->val.node);
            break;

        case k_NodeKindStatementWhile:
            printf("while ");
            prettyNode(e->val.whileStatement.exp);
            printf("\n{ \n");
            prettyNode(e->val.whileStatement.statements);
            printf("}\n");
            break;
	}
}
