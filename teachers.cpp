#include <bits/stdc++.h>
using namespace std ;

#define NAME_LENGTH       (32)    /* ����� ����� ������� */
#define EOL               (10)    /* END OF LINE - ����� ������ */

char teachers[500];
const char *week_days[5];
char week_day_name[251];

int read_day_names (){
    FILE *fp;

    fp = fopen( "days.txt", "r" );
    for ( int i = 0; i < 5; i++ ){
        week_days[i] = &week_day_name[i*50];
        fscanf( fp, "%s", week_days[i] );
    }
    fclose(fp);
}


int write_line ( int j, char *ll, char *rl, FILE *fc ){
    fprintf ( fc, " <tr>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;
    if ( strlen ( ll ) == 0 ) fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    fprintf ( fc, ">%d", j+1 ) ;            /// ����� ����� � ����� ������
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;
    if ( strlen ( ll ) == 0 ) fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    fprintf ( fc, ">%s" , ll  ) ;              /// �������� ����� � ����� ������
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"8%%\"" ) ;    /// ������������� ����� ������-�����������
    fprintf ( fc, " style = \"background:lightgrey\">"  ) ;
    fprintf ( fc, "</td>\n" ) ;


    fprintf ( fc, "  <td width=\"8%%\"" ) ;
    if ( strlen ( rl ) == 0 ) fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    if ( j != 3 ) fprintf ( fc, ">%d", j + 5 ) ;            /// ����� ����� � ������ ������
    else fprintf( fc, ">" );
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, "  <td width=\"38%%\"" ) ;
    if ( strlen ( rl ) == 0 ) fprintf ( fc, " style = \"background:lightgrey\""  ) ;
    fprintf ( fc, ">%s" , rl  ) ;              /// �������� ����� � ������ ������
    fprintf ( fc, "</td>\n" ) ;

    fprintf ( fc, " </tr>\n" ) ;

    return 0;
}


/// �� �������� ��� daily (0=��,1=��,2=��,3=��,4=��) � ������� � ���������� ������� �� ������ ���� ����� ���,
/// ���������� � html-���� ������ (fc) ���������� ������� ���
int write_day ( const char* daily, int i, FILE* fc ){
    int x = 0; /// ��������� ����� �������� ���� ������ ������� ���
    char *ls[8]; /// ��������� �� �������� ������
    ls[7] = &teachers[i-1]; /// 8-� ���� ������ ������

    for ( int j = 0; j < 7; j++ ){ /// ������� �������� ���� ������ ������� ���
        ls[j] = &teachers[i];
        while ( teachers[i] != ';' && teachers[i] != EOL ) i++;  /// ���� ������ �������� ���������� �����
        teachers[i++] = '\0';
    }

    for ( int j = 0; j < 7; j++ ) x += strlen ( ls[j] );

    if ( x ){                   /// ���� ���� ���� �� ���� ���� � ���� ����
        fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
        fprintf ( fc, "%s</label><br>\n", daily ) ;                     /// �������� ��� ������

        fprintf ( fc, "<table width=\"100%%\" cols = \"5\" rules=\"all\" " ) ;
        fprintf ( fc, "style = \"border: 3px solid black; background: white; border-collapse;" );
        fprintf ( fc, "font-size: 4em\">\n" );

        for ( int j = 0; j < 4; j++ )        /// j = ����� ���� ������: (1,5), (2,6), (3,7), (4,_)
            write_line( j, ls[j], ls[j+4], fc );
        fprintf( fc, "</table>\n\n");
    }

    return i;
}

int write_teacher ( char *tname){
    FILE *tn;
    int i ;                       /// ��������� ��� �����
    for ( i = 0 ; i < NAME_LENGTH; i++ )
        if ( tname[i] == ';' ){
            tname[i++] = '.'; tname[i++] = 'h';tname[i++] = 't';tname[i++] = 'm';tname[i++] = 'l';tname[i++] = '\0';
            break;
        }

    tn = fopen( tname, "w" );

    fprintf ( tn, "<html>\n" ) ;
    fprintf ( tn, "<body style=\"background-color: lightgrey\"; >\n" ) ;
    fprintf ( tn, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" ) ;

    for ( i = 0; teachers[i] != ';' ; i++ ) ; /// �������� ��� ������� � ������ UTF-8
    teachers[i] = '\0';

    fprintf ( tn, "<label style=\"font-size: 4em; font-weight: bold\">" ) ;
    fprintf ( tn, "%s</label><br>\n\n", teachers ) ;         /// ��� ������� � ����� ����� �������

    i++;
    for ( int j = 0; j < 5; j++ ) /// j - ���� ������: (0=��,1=��,2=��,3=��,4=��)
        i = write_day ( week_days[j], i, tn );

    fprintf ( tn, "\n</body>\n</html>\n" ) ;
    fclose(tn);
}

/// ������������ �����-���������� rt.html � ��� �������
/// ����� :
int write_head ( FILE *fc ){
    fprintf ( fc, "<html>\n" ) ;
    fprintf ( fc, "<body style=\"background-color: lightgrey\"; >\n" ) ;
    fprintf ( fc, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" ) ;
    fprintf ( fc, "<label style=\"font-size: 4em; font-weight: bold\">" );
    fprintf ( fc, "���������� ��������</label><br>\n\n" ) ;


    fprintf ( fc, "<table width=\"100%%\" cols = \"2\" rules=\"none\" " ) ;
    fprintf ( fc, "style = \"border: 5px solid black; background: white; border-collapse;" );
    fprintf ( fc, "font-size: 2em\">\n" );

    return 0;
}

/// ���������� ������ ������� ��������
int write_rt ( char *tname, int x, FILE *fc ){
    int len;
    len = strlen(tname) - 5;
    tname[len] = '\0';

    if ( x%2 == 0 ){
         fprintf ( fc, " <tr>\n" ) ;

        fprintf ( fc, "  <td width=\"50%%\" style=\"font-size: 2em; border: 5px solid black;\">" ) ;
        fprintf ( fc, "<a href=\"%s.html\">%s</a>", tname, tname );
        fprintf ( fc, "</td>\n" ) ;

///        fprintf ( fc, "  <td width=\"10%%\"" ) ;    /// ������������� ����� ������-�����������
///        fprintf ( fc, " style = \"background:lightgrey\">"  ) ;
///        fprintf ( fc, "</td>\n" ) ;
        }
    else{
///        fprintf ( fc, "  <td width=\"50%%\"" ) ;
        fprintf ( fc, "  <td width=\"50%%\" style=\"font-size: 2em; border: 5px solid black;\"" ) ;
        if ( len <= 1 )fprintf ( fc, " style = \"background:lightgrey\">"  );
        else fprintf( fc, ">" );
        fprintf ( fc, "<a href=\"%s.html\">%s</a>", tname, tname );
        fprintf ( fc, "  </td>\n" ) ;
        fprintf ( fc, " </tr>\n" );
    }

    return 0;
}

int main ( ) {
    FILE *ft, *rt, *ft1, *fc;
    int x = 0;                              /// ���������� ����������� ��������
    ft  = fopen ( "�������.csv",  "r" );    /// � ��������� UTF-8
    ft1 = fopen ( "�������1.csv", "r" );    /// � ��������� ANSI � ��� �� ����������
    read_day_names(); /// � ��������� UTF-8 ��������� �������� ���� ������ � ���������� ������ week_day_name[251];
    if ( ft == NULL || ft1 == NULL ) {
        cout << "open error";
        return 0;
    }

    fc = fopen( "rt.html", "w" );
    write_head(fc);

    for ( ;; ){
        char teachers1[500]; /// ����� �������� � ��������� ANSI
        char *teach, *teach1;
        teach = fgets( teachers, 480, ft ); /// teachers[] - ���������� ������-��������� ������
        teach1 = fgets( teachers1, 480, ft1 );
        if ( teach == NULL || teach1 == NULL ) break;
        else {
                write_teacher( teachers1 );     /// �������� ����� html ��� ������� teachers1
                write_rt(teachers1, x++, fc);   /// ���������� ������ � ������� rt.html
        }
    }

    fclose(ft1);
    fclose(ft);

    if ( x % 2 ) {   /// ���������� ������ ������ ������, ���� �������� �������� ����������
            char nemo[6] = {0};
            write_rt ( nemo, x, fc );
    }
    fprintf ( fc, "\n</table>\n</body>\n</html>\n" ) ;
    fclose ( fc ) ;
    cout << x << " teachers in the table\n" ;
    return 0 ;
}
