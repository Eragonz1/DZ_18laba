#include <stdio.h>
#include <string.h>
#include <time.h>

struct Date {
    int day;
    int month;
    int year;
};

typedef struct {
    char surname[30];
    char name[30];
    char patronymic[30];
    char position[50];
    char gender;
    struct Date hire_date;
} Employee;

struct Date get_current_date();
double calculate_experience(struct Date hire_date);
void print_employee(Employee emp, double staj);

int main() {
    int i, n;
    Employee employees[10];
    double staj[10];
    double total_years = 0, avg_years;

    printf("Сколько сотрудников добавить(от 5 до 10): ");
    scanf("%d", &n);

    if (n < 5 || n > 10) {
        printf("Ошибка - введите от 5 до 10 сотрудников\n");
        return 1;
    }

    printf("\nВвод данных сотрудников\n");
    for (i = 0; i < n; i++) {
        printf("\n---Сотрудник %d---\n", i + 1);

        printf("Фамилия: ");
        scanf("%s", employees[i].surname);

        printf("Имя: ");
        scanf("%s", employees[i].name);

        printf("Отчество: ");
        scanf("%s", employees[i].patronymic);

        printf("Должность: ");
        scanf("%s", employees[i].position);

        printf("Пол (М/Г): ");
        scanf(" %c", &employees[i].gender);

        printf("Дата приема (день месяц год): ");
        scanf("%d %d %d", &employees[i].hire_date.day, &employees[i].hire_date.month, &employees[i].hire_date.year);
    }

    printf("\n---Расчет стажа---\n");
    for (i = 0; i < n; i++) {
        staj[i] = calculate_experience(employees[i].hire_date);
        total_years += staj[i];

        printf("%s %s: %.1f лет\n", employees[i].surname, employees[i].name, staj[i]);
    }
    avg_years = total_years / n;
    printf("\nСредний стаж: %.1f лет\n", avg_years);


    printf("\n---Сотрудники со стажем выше среднего---\n");
    int count = 0;
    for (i = 0; i < n; i++) {
        if (staj[i] > avg_years) {
            print_employee(employees[i], staj[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("Таких сотрудников нет.\n");
    }
    else {
        printf("\nНайдено: %d сотрудников\n", count);
    }

    return 0;
}

struct Date get_current_date() {
    struct tm* mytime;
    time_t t;
    t = time(NULL);
    mytime = localtime(&t);

    struct Date current;
    current.day = mytime->tm_mday;
    current.month = mytime->tm_mon + 1;
    current.year = mytime->tm_year + 1900;

    return current;
}

double calculate_experience(struct Date hire_date) {
    
    struct Date current = get_current_date();
    int days = (current.year - hire_date.year) * 365 + (current.month - hire_date.month) * 30 + (current.day - hire_date.day);

    if (days < 0) {
        return 0;
    }

    return days / 365.0;
}

void print_employee(Employee emp, double staj) {
    printf("\n--- Сотрудник ---\n");
    printf("Фамилия: %s\n", emp.surname);
    printf("Имя: %s\n", emp.name);
    printf("Отчество: %s\n", emp.patronymic);
    printf("Должность: %s\n", emp.position);
    printf("Пол: %c\n", emp.gender);
    printf("Дата приема: %02d.%02d.%d\n", emp.hire_date.day, emp.hire_date.month, emp.hire_date.year);
    printf("Стаж: %.1f лет\n", staj);
}