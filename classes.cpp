#include <bits/stdc++.h>
using namespace std ;

#define UROK_LENGTH       (10)    /* длина ячейки для урока, из них 1 байт нулевой - конец строки */
#define NUMBER_OF_CLASSES (22)    /* количество классов */
#define UROKS_IN_WEEK     (35)    /* 5 дней по 7 уроков */
#define EOL               (10)    /* END OF LINE - конец строки */

char uroks [UROK_LENGTH * NUMBER_OF_CLASSES * UROKS_IN_WEEK] = { 0 }; /// массив всех уроков в таблице

/// функции read_csv_file_for_classes () и read_urok() читают данные из входного файла "classes.csv"

/// Ф-ция читает очередной урок и возвращает указатель на следующий, либо NULL, если достигнут конец файла
/// по ходу работы функции заполняется глобальный массив uroks[]
char* read_urok ( char* u, FILE* fp ) {
    int read_symbol ;
    char* next ;
    next = u + UROK_LENGTH ;

    for ( ; u < next - 1 ; u++ ) {
        read_symbol = fgetc ( fp ) ;

             if (                             read_symbol == EOF ) { *u = '\0' ; return NULL ; }
        else if ( (char)read_symbol == ';' || read_symbol == EOL ) { *u = '\0' ; return next ; }
        else if ( (char)read_symbol == '(' ||
                  (char)read_symbol == '.' ||
                  (char)read_symbol == ',' ||
                  (char)read_symbol == ' ' )                       { *u = '\0' ; break ; }
        else *u = (char)read_symbol ;
    }

    while ( 1 ) {
        read_symbol = fgetc ( fp ) ;
        if ( read_symbol == EOF                             ) return NULL ;
        if ( read_symbol == EOL || (char)read_symbol == ';' ) return next;
    }
}

/// Полностью читает весь входной файл "classes.csv"
int read_csv_file_for_classes ( ) {
    FILE* fp ;
    int num_of_read_uroks = 0 ; /// количество прочитанных уроков из таблицы

    fp = fopen( "classes.csv" , "r" ) ;
    if ( fp == NULL ) { cout << "Error: file classes.csv not opened" ; return -1 ; }

    for ( char* u = uroks ; u != NULL ; num_of_read_uroks++ ) u = read_urok ( u , fp ) ;

    fclose ( fp ) ;
    return num_of_read_uroks - 1 ;
}


/// функции write_class(), write_day () и write_line () формируют результирующий html файл для
/// одного указанного класса

/// По номеру урока и указателю на данный урок записывает в файл класса строчку из
/// пары уроков: nl=0: уроки 1 и 5;  nl=1: уроки 2 и 6; nl=2: уроки 3 и 7; nl=3: уроки 4 и пустой.
/// Пустой урок записывается серым цветом
int write_line ( int nl, char* fl, FILE* fc ){
    fprintf ( fc, " <tr>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;
    fprintf ( fc, ">%d", nl + 1 ) ;            /// номер урока в левой клетке
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;
    fprintf ( fc, ">%s" , fl  ) ;              /// название урока в левой клетке
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;    /// промежуточная серая клетка-разделитель
    fprintf ( fc, " style = \"background:lightgrey\">"  ) ;
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;    /// номер урока в правой клетке
    if ( strlen ( fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) == 0 || nl == 3 )
          fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    if ( nl == 3 ) fprintf( fc, ">" );          /// если урок пустой, либо 8-й, то клетка серая
    else fprintf ( fc, ">%d", nl + 5 ) ;        /// если урок 8-й, то номер урока не пишем
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;    /// название урока в правой клетке
     if ( strlen ( fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) == 0 || nl == 3 )
          fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    if ( nl == 3 ) fprintf( fc, ">" );          /// если урок пустой, либо 8-й, то клетка серая
    else fprintf ( fc, ">%s" , fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) ;
    fprintf ( fc, "</td>\n" ) ;                 /// если урок 8-й, то название урока не пишем

    fprintf ( fc, " </tr>\n" ) ;
    return 0;
}

/// По номеру дня daily (0=пн,1=вт,2=ср,3=чт,4=пт) и указателю на первый урок этого дня,
/// записывает в html-файл класса (fc) расписание данного дня
int write_day ( const char* daily, char* first_lesson, FILE* fc ){

    fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
    fprintf ( fc, "%s</label><br>\n", daily ) ;                     /// название дня недели

    fprintf ( fc, "<table width=\"100%%\" cols = \"5\" rules=\"all\" " ) ;
    fprintf ( fc, "style = \"border: 3px solid black; background: white; border-collapse;" );
    fprintf ( fc, "font-size: 4em\">\n" );

    for ( int i = 0; i < 4; i++ )        /// i = номер пары уроков
        write_line( i, first_lesson + i*NUMBER_OF_CLASSES*UROK_LENGTH, fc );

    fprintf( fc, "</table>\n\n");
    return 0;
}

/// создаёт и записывает html файл для класса номер cl_num
/// нумерация начинается с 0 = "5А", далее идёт по колонкам исходной таблицы
int write_class ( int cl_num ){
    FILE* fc;
    static const char *names_of_classes [NUMBER_OF_CLASSES] = {
        "5А", "5Б", "5В", "6А", "6Б", "6В", "7А", "7Б", "7В", "7К", "8А", "8Б", "8В",
        "9А", "9Б", "9В", "10А", "10Б", "10В", "11А", "11Б", "11В" } ;
    static const char *week_days[5] = {
    "Понедельник:", "Вторник:", "Среда:", "Четверг:", "Пятница:" } ;

    char file_name[9] ;
    sprintf( file_name, "%s.html", names_of_classes [cl_num] );

    fc = fopen( file_name, "w" );

    fprintf ( fc, "<html lang=\"ru\">\n" ) ;
    fprintf ( fc, "<body style=\"background-color: lightgrey\"; >\n" ) ;

    fprintf ( fc, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" ) ;

    fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
    fprintf ( fc, "%s</label><br>\n\n", names_of_classes[cl_num] ) ;         /// имя класса

    for ( int i = 0; i < 5; i++ ) /// i - день недели: (0=пн,1=вт,2=ср,3=чт,4=пт)
        write_day ( week_days[i], uroks + (7*i*NUMBER_OF_CLASSES + cl_num)*UROK_LENGTH, fc );

    fprintf ( fc, "\n</body>\n</html>\n" ) ;

    fclose( fc ) ;
    return 0 ;
}

int main () {
    cout << read_csv_file_for_classes ( ) ;

/// i - номер класса
/// нумерация начинается с 0 = "5А", далее идёт по колонкам исходной таблицы
    for ( int i = 0; i < NUMBER_OF_CLASSES; i++ ) write_class ( i ) ;
    return 0 ;
}
