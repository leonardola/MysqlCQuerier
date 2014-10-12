/* Simple C program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showResult(MYSQL *conn, MYSQL_RES *answer) {

    MYSQL_ROW row;
    unsigned int numberOfFields = mysql_num_fields(answer);
    int i=0;
    
    while ((row = mysql_fetch_row(answer)) != NULL){
      
        for (i=0;i < numberOfFields;i++){
          
            printf("%s\t", row[i]);
        
        }
      
        printf("\n");
    
    }
    
}

/**
 * executa a query na conexão recebida
 * @param conn MYSQL
 */
void executeQuery(MYSQL *conn) {
    
    setbuf(stdin,NULL);
    
    char *query[500];
    
    setbuf (stdin, NULL);
    
    printf("Digite uma query valida\n");
    gets(query);
    
    printf("%s",query);
    //scanf("%[^\n]s",query);
    
    if (mysql_query(conn, query)) {
        printf("Erro ao executar query %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *answer = mysql_use_result(conn);

    showResult(conn, answer);

}

int main() {

    char *user = "ifc";
    char *password = "password"; /* set me first */
    char *database = "foo";
    char *server[15];
    
    printf("Digite o ip do host\n");
    scanf("%s",server);
    
    

    

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL/*port*/, 0)) {

        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);

    }
    /* send SQL query */
    if (mysql_query(conn, "show tables")) {

        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);

    }

    res = mysql_use_result(conn);

    /* output table name */
    printf("MySQL Tables in mysql database:\n");

    while ((row = mysql_fetch_row(res)) != NULL) {

        printf("%s \n", row[0]);

    }

    /* close connection */
    executeQuery(conn);


    //close connection
    mysql_free_result(res);
    mysql_close(conn);

}