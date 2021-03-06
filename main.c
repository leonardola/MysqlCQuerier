/* Simple C program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * mostra o resultado de uma query
 * @param conn
 * @param answer
 */
void showResult(MYSQL *conn, char *query){
    
    if (mysql_query(conn, query)) {
        printf("Erro ao executar query %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *answer = mysql_use_result(conn);

    if(answer == NULL){
        mysql_free_result(answer);
        return ;
    }
    
    MYSQL_ROW row;
    unsigned int numberOfFields = mysql_num_fields(answer);
    int i=0;
    
    
            
    while ((row = mysql_fetch_row(answer)) != NULL){
      
        for (i=0;i < numberOfFields;i++){
          
            printf("%s\t", row[i]);
        
        }
      
        printf("\n");
    
    }
    
    printf("\n");
    
}

/**
 * mostra os bancos disponiveis
 * @param conn
 */
void showDatabases(MYSQL *conn){
    
    showResult(conn,"show databases");
    
}

/**
 * mostra as tabelas do banco selecionado
 * @param conn
 */
void showTables(MYSQL *conn){
    
    showResult(conn,"show tables");
    
}



/**
 * executa a query na conexão recebida
 * @param conn MYSQL
 */
int executeQuery(MYSQL *conn) {
    
    setbuf(stdin,NULL);
    
    char query[500];
    
    int flag = 0;
    
    while(!flag){
        setbuf (stdin, NULL);

        printf("Digite uma query valida\n");
        gets(query);
        
        if(strcmp(query,"menu") == 0){
            return 1;
        }else if(strcmp(query,"sair") == 0){
            return 0;
        }

        showResult(conn,query);
        
    }
    return 0;
}

/**
 * permite trocar de banco 
 * @param conn
 * @return 
 */
int selectDatabase(MYSQL *conn){
    char dataBase[50];
    
    
    printf("Digite o nome do banco de dados\n");
    scanf("%s",dataBase);
    
    if(strcmp(dataBase,"menu") == 0){
        
        return 1;
        
    }else if(strcmp(dataBase,"sair") == 0){
        
        return 0;
        
    }
    
    if(mysql_select_db(conn, dataBase)){
        
        printf("erro ao conectar no banco de dados");
        return 1;
    }
    
}

/**
 * mostra o menu
 */
int showMenu(MYSQL *conn){
    
    int option;
    int flag = 1; 

    while(flag){
        printf("----------------Menu---------------\n");
        printf("Digite 1 para sair \n");
        printf("Digite 2 para executar uma query manual \n");
        printf("Digite 3 para mostrar os bancos \n");
        printf("Digite 4 para selecionar um banco \n");
        printf("Digite 5 para mostrar as tabelas do banco \n");

        scanf("%i",&option);
    
        switch(option){
            case 1:
                return 0;
            break;

            case 2:
                if(executeQuery(conn) == 0){
                    return 0;
                }
            break;

            case 3:
                showDatabases(conn);
            break;

            case 4:
                selectDatabase(conn);
            break;

            case 5:
                showTables(conn);
            break;

        }
        
    }
    
    return 0;
    
}


int main() {

    char user[50];
    char password[50]; 
    char database[50];
    char server[15];
    
    printf("Digite o ip do host\n");
    scanf("%s",server);
    
    printf("Digite o nome do usario\n");
    scanf("%s",user);
   
    printf("Digite o a senha\n");
    scanf("%s",password);
    
    printf("Digite o nome do banco de dados \n");
    scanf("%s",database);
    
    printf("\n\n\n Digite a qualquer momento 'menu' para ir para o menu\n");
    printf("Ou 'sair' par terminar \n\n\n");
    
    MYSQL *conn;
    //cria uma conexão fazia
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL/*port*/, 0)) {

        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);

    }
    
    //permite o usuario digitar uma query ou entrar no menu
    if(executeQuery(conn) == 1){
        showMenu(conn);
    }

    //fecha a conexão
    mysql_close(conn);

}