# include <stdio.h>

// array multidim. El primero es el numero de dias del mes i en año no bisiesto. El segundo es lo mismo en bisiesto
static int daytab[2] [13] = {       // static porque queremos que sea visible a todas las funciones del fichero
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// day_of_year: obtiene el día del año a partir del día y mes

int day_of_year (int year, int month, int day) {
    int i, leap;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;

    if ((month<=0 || month > 12) || (day>daytab[leap][month] || day<=0)) {
        printf("Error en los parametros de entrada");
        return -1;
    }
    else {
        // si el año es bisiesto, cogemos el daytab[1], si no, daytab[0]
        for (i=0; i<month; i++)
            day += daytab[leap][i];
        return day;
    }
}

int day_of_year2 (int year, int month, int day) {
    int leap;
    int *i;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;

    if ((month<=0 || month > 12) || (day>daytab[leap][month] || day<=0)) {
        printf("Error en los parametros de entrada");
        return -1;
    }
    else {
        // si el año es bisiesto, cogemos el daytab[1], si no, daytab[0]
        for (i=daytab[leap]; i-daytab[leap]<month; i++)
            day += *i;
        return day;
    }
}

// month_day: obtiene dia/mes a partir del dia del año
// notar que, como la función tiene que regresar dos valores, conviene que en vez de un return tenga dos `
// punteros como argumentos, que reciban la salida

void month_day (int year, int yearday, int *month, int *day) {
    int i, leap;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;

    if (yearday <= 0 || yearday > 365+leap || year <= 0) {
        printf("Error en los parametros de entrada\n");
        *month = *day = -1;
    }

    else {
        for (i=1; yearday>daytab[leap][i]; i++)
            yearday -= daytab[leap][i];
        *month = i;
        *day = yearday;
    }
}

void month_day2 (int year, int yearday, int *month, int *day) {
    int *i, leap;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;

    if (yearday <= 0 || yearday > 365+leap || year <= 0) {
        printf("Error en los parametros de entrada\n");
        *month = *day = -1;
    }

    else {
        for (i=daytab[leap]; yearday>*i; i++)
            yearday -= *i;
        *month = i-daytab[leap];
        *day = yearday;
    }
}

// month_name: regresa un puntero a una cadena que contiene el nombre del n-esimo mes
char *month_name(int n) {
    // declaracion de un array de punteros (array de arrays de caracteres)
    static char *name[] = {"Mes ilegal", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    if (n>12) {
        printf("Mes ilegal");
        return name[0];
    }
    else {
        return name[n];
    }
}


int main() {
    int *month, *day;
    printf("%d\n", day_of_year2(2015, 2, 28));
    month_day(2016, 366, month, day);
    printf("%d / %d", *day, *month);

    // tmb puede definirse int month, day y pasarle a la funcion month_day las posiciones de memoria con & --> equivalente

    return 0;
}