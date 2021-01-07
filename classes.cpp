#include <bits/stdc++.h>
using namespace std ;

#define UROK_LENGTH       (10)    /* ����� ������ ��� �����, �� ��� 1 ���� ������� - ����� ������ */
#define NUMBER_OF_CLASSES (22)    /* ���������� ������� */
#define UROKS_IN_WEEK     (35)    /* 5 ���� �� 7 ������ */
#define EOL               (10)    /* END OF LINE - ����� ������ */

char uroks [UROK_LENGTH * NUMBER_OF_CLASSES * UROKS_IN_WEEK] = { 0 }; /// ������ ���� ������ � �������

/// ������� read_csv_file_for_classes () � read_urok() ������ ������ �� �������� ����� "classes.csv"

/// �-��� ������ ��������� ���� � ���������� ��������� �� ���������, ���� NULL, ���� ��������� ����� �����
/// �� ���� ������ ������� ����������� ���������� ������ uroks[]
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

/// ��������� ������ ���� ������� ���� "classes.csv"
int read_csv_file_for_classes ( ) {
    FILE* fp ;
    int num_of_read_uroks = 0 ; /// ���������� ����������� ������ �� �������

    fp = fopen( "classes.csv" , "r" ) ;
    if ( fp == NULL ) { cout << "Error: file classes.csv not opened" ; return -1 ; }

    for ( char* u = uroks ; u != NULL ; num_of_read_uroks++ ) u = read_urok ( u , fp ) ;

    fclose ( fp ) ;
    return num_of_read_uroks - 1 ;
}


/// ������� write_class(), write_day () � write_line () ��������� �������������� html ���� ���
/// ������ ���������� ������

/// �� ������ ����� � ��������� �� ������ ���� ���������� � ���� ������ ������� ��
/// ���� ������: nl=0: ����� 1 � 5;  nl=1: ����� 2 � 6; nl=2: ����� 3 � 7; nl=3: ����� 4 � ������.
/// ������ ���� ������������ ����� ������
int write_line ( int nl, char* fl, FILE* fc ){
    fprintf ( fc, " <tr>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;
    fprintf ( fc, ">%d", nl + 1 ) ;            /// ����� ����� � ����� ������
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;
    fprintf ( fc, ">%s" , fl  ) ;              /// �������� ����� � ����� ������
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;    /// ������������� ����� ������-�����������
    fprintf ( fc, " style = \"background:lightgrey\">"  ) ;
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;    /// ����� ����� � ������ ������
    if ( strlen ( fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) == 0 || nl == 3 )
          fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    if ( nl == 3 ) fprintf( fc, ">" );          /// ���� ���� ������, ���� 8-�, �� ������ �����
    else fprintf ( fc, ">%d", nl + 5 ) ;        /// ���� ���� 8-�, �� ����� ����� �� �����
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;    /// �������� ����� � ������ ������
     if ( strlen ( fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) == 0 || nl == 3 )
          fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    if ( nl == 3 ) fprintf( fc, ">" );          /// ���� ���� ������, ���� 8-�, �� ������ �����
    else fprintf ( fc, ">%s" , fl + NUMBER_OF_CLASSES*UROK_LENGTH*4 ) ;
    fprintf ( fc, "</td>\n" ) ;                 /// ���� ���� 8-�, �� �������� ����� �� �����

    fprintf ( fc, " </tr>\n" ) ;
    return 0;
}

/// �� ������ ��� daily (0=��,1=��,2=��,3=��,4=��) � ��������� �� ������ ���� ����� ���,
/// ���������� � html-���� ������ (fc) ���������� ������� ���
int write_day ( const char* daily, char* first_lesson, FILE* fc ){

    fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
    fprintf ( fc, "%s</label><br>\n", daily ) ;                     /// �������� ��� ������

    fprintf ( fc, "<table width=\"100%%\" cols = \"5\" rules=\"all\" " ) ;
    fprintf ( fc, "style = \"border: 3px solid black; background: white; border-collapse;" );
    fprintf ( fc, "font-size: 4em\">\n" );

    for ( int i = 0; i < 4; i++ )        /// i = ����� ���� ������
        write_line( i, first_lesson + i*NUMBER_OF_CLASSES*UROK_LENGTH, fc );

    fprintf( fc, "</table>\n\n");
    return 0;
}

/// ������ � ���������� html ���� ��� ������ ����� cl_num
/// ��������� ���������� � 0 = "5�", ����� ��� �� �������� �������� �������
int write_class ( int cl_num ){
    FILE* fc;
    static const char *names_of_classes [NUMBER_OF_CLASSES] = {
        "5�", "5�", "5�", "5�", "6�", "6�", "6�", "7�", "7�", "7�", "8�", "8�", "8�",
        "9�", "9�", "9�", "10�", "10�", "10�", "11�", "11�", "11�" } ;
    static const char *week_days[5] = {
    "�����������:", "�������:", "�����:", "�������:", "�������:" } ;

    char file_name[9] ;
    sprintf( file_name, "%s.html", names_of_classes [cl_num] );

    fc = fopen( file_name, "w" );

    fprintf ( fc, "<html>\n" ) ;
    fprintf ( fc, "<body style=\"background-color: lightgrey\"; >\n" ) ;

    fprintf ( fc, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" ) ;

    fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
    fprintf ( fc, "%s</label><br>\n\n", names_of_classes[cl_num] ) ;         /// ��� ������

    for ( int i = 0; i < 5; i++ ) /// i - ���� ������: (0=��,1=��,2=��,3=��,4=��)
        write_day ( week_days[i], uroks + (7*i*NUMBER_OF_CLASSES + cl_num)*UROK_LENGTH, fc );

    fprintf ( fc, "\n</body>\n</html>\n" ) ;

    fclose( fc ) ;
    return 0 ;
}

int main () {
    cout << read_csv_file_for_classes ( ) ;

/// i - ����� ������
/// ��������� ���������� � 0 = "5�", ����� ��� �� �������� �������� �������
    for ( int i = 0; i < NUMBER_OF_CLASSES; i++ ) write_class ( i ) ;
    return 0 ;
}
