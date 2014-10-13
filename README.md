MysqlCQuerier
=============

Precisa ser compilado com:

no OSX: gcc -I /usr/local/mysql/include -L/usr/local/mysql/lib -lmysqlclient

no linux: gcc version.c -o version `mysql_config --cflags --libs` 

não são aspas simples são acentos -> `mysql_config —cflags —-libs`

