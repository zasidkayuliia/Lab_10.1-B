#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Spec {
    KOMPUTERNI_NAYKU,
    INFORMATUKA,
    MATEMATUKA_TA_EKONOMIKA,
    FIZUKA_TA_INFORMATUKA,
    TRYDOVE_NAVCHANNYA
};

string specStr[] = {
      "Комп'ютерні науки",
      "Інформатика",
      "Математика та економіка",
      "Фізика та інформатика",
      "Трудове навчання"
};

struct Student {
    string prizv;
    int kurs;
    Spec spec;
    int mark_fizuka;
    int mark_matematuka;
    union
    {
        int mark_programyvanna;
        int mark_chuselnimetodu;
        int mark_pedahohika;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double LineSearch(Student* p, const int N);
void CountGoodMarks(Student* p, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    double proc = LineSearch(p, N);
    cout << "Процент студентів, які отримали з фізики і математики оцінку 5: ";
    cout << fixed << setprecision(2) << proc << "%" << endl;

    CountGoodMarks(p, N);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс : "; cin >> p[i].kurs;
        cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка,\n"
            << " 3 - фізика та інформатика, 4 - трудове навчання): "; cin >> spec;
        p[i].spec = (Spec)spec;
        cout << " оцінка з фізики: "; cin >> p[i].mark_fizuka;
        cout << " оцінка з математики: "; cin >> p[i].mark_matematuka;

        switch (p[i].spec)
        {
        case KOMPUTERNI_NAYKU:
            cout << " оцінка з програмування : "; cin >> p[i].mark_programyvanna;
            break;
        case  INFORMATUKA:
            cout << " оцінка з чисельних методів : "; cin >> p[i].mark_chuselnimetodu;
            break;
        case MATEMATUKA_TA_EKONOMIKA:
        case FIZUKA_TA_INFORMATUKA:
        case TRYDOVE_NAVCHANNYA:
            cout << " оцінка з педагогіки : "; cin >> p[i].mark_pedahohika;
            break;
        }
        cout << endl;
    }
}
  

void Print(Student* p, const int N) {
    cout << "==============================================================================================================================" << endl;
    cout << "| №  |  Прізвище       | Курс |    Спеціальність         | Фізика | Математика | Програмування| Чисельні методи | Педагогіка |" << endl;
    cout << "==============================================================================================================================" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(16) << left << p[i].prizv;
        cout << "| " << setw(4) << right << p[i].kurs << " ";
        cout << "| " << setw(25) << left << specStr[p[i].spec];
        cout << "| " << setw(6) << right << p[i].mark_fizuka << " ";
        cout << "| " << setw(10) << right << p[i].mark_matematuka << " ";

        if (p[i].spec == KOMPUTERNI_NAYKU) {
            cout << "| " << setw(12) << right << p[i].mark_programyvanna << " ";
            cout << "| " << setw(15) << right << " " << " "; 
            cout << "| " << setw(10) << right << " " << " |"; 
        }
        else if (p[i].spec == INFORMATUKA) {
            cout << "| " << setw(12) << right << " " << " ";  
            cout << "| " << setw(15) << right << p[i].mark_chuselnimetodu << " ";
            cout << "| " << setw(10) << right << " " << " |";
        }
        else {
            cout << "| " << setw(12) << right << " " << " ";  
            cout << "| " << setw(15) << right << " " << " ";  
            cout << "| " << setw(10) << right << p[i].mark_pedahohika << " |"; 
        }

        cout << endl;
    }

    cout << "==============================================================================================================================" << endl;
    cout << endl;
}

double LineSearch(Student* p, const int N) {
    string result;
    int k = 0;

    for (int i = 0; i < N; i++) {
        if (p[i].mark_fizuka == 5 && p[i].mark_matematuka == 5) {
            if (k > 0) result += ", ";
            result += p[i].prizv;
            k++;
        }
    }

    if (k > 0) {
        cout << "Прізвища студентів, які отримали з фізики і математики оцінку 5: ";
        cout << result << endl;
    }
    else {
        cout << "Немає студентів, які отримали з фізики і математики оцінку 5." << endl;
    }

    return 100.0 * k / N;
}

void CountGoodMarks(Student* p, const int N) {
    int goodPhysics = 0;
    int goodMath = 0;
    int goodProgramming = 0;
    int goodChuselnimetodu = 0;
    int goodPedahohica = 0;

    for (int i = 0; i < N; i++) {
        if (p[i].mark_fizuka == 4) goodPhysics++;
        if (p[i].mark_matematuka == 4) goodMath++;

        switch (p[i].spec) {
        case KOMPUTERNI_NAYKU:
            if (p[i].mark_programyvanna == 4) goodProgramming++;
            break;
        case INFORMATUKA:
            if (p[i].mark_chuselnimetodu == 4) goodChuselnimetodu++;
            break;
        case MATEMATUKA_TA_EKONOMIKA:
        case FIZUKA_TA_INFORMATUKA:
        case TRYDOVE_NAVCHANNYA:
            if (p[i].mark_pedahohika == 4) goodPedahohica++;
            break;
        }
    }

    cout << "Кількість оцінок 'добре' (4) з кожного предмету:" << endl;
    cout << "Фізика: " << goodPhysics << endl;
    cout << "Математика: " << goodMath << endl;
    cout << "Програмування: " << goodProgramming << endl;
    cout << "Чисельні методи: " << goodChuselnimetodu << endl;
    cout << "Педагогіка: " << goodPedahohica << endl;
}
