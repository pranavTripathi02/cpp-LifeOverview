#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

static constexpr int months[12] = {31, 28, 31, 30, 31, 30,
                                   31, 31, 30, 31, 30, 31};

class Date {
  int dd, mm, yy;

public:
  bool verifyDob(Date &d2) {
    if (mm > 12 || mm < 1)
      return 1;
    if (dd > months[mm - 1] || dd < 1)
      return 1;
    if (yy > d2.yy || (yy == d2.yy && mm > d2.mm) ||
        (yy == d2.yy && mm == d2.mm && dd > d2.dd)) {
      return 1;
    }
    return 0;
  }
  void inputDate() {
    cout << "\nEnter your date of birth following the prompts given.\n";
    cout << "\nEnter the date:\t";
    cin >> dd;
    cout << "\nEnter the month(index):\t";
    cin >> mm;
    cout << "\nEnter the year:\t";
    cin >> yy;
  }
  string getDate() {
    string s = "";
    s += to_string(yy) + "-";
    s += to_string(mm) + "-";
    s += to_string(dd) + "-";
    return s;
  }
  void setDate(int n_year, int n_mon, int n_date) {
    dd = n_date;
    mm = n_mon;
    yy = n_year;
  }
  int calcDays(Date &d2) {
    int yDays = (d2.yy - yy) * 365; // calc days for every year since

    int remDays = (months[d2.mm - 1] - d2.dd); // days remaining this year
    for (int i = d2.mm; i < 12; i++) {
      remDays += months[i];
    }

    yDays -= remDays;

    int bMDays = months[mm - 1] - dd;
    // int remMonths = 12-mm;
    int dMonths = 0;
    for (int i = mm; i < 12; i++) {
      dMonths += months[i];
    }

    // cout << "\nyDays: " << yDays;
    // cout << "\nbMDays: " << bMDays;
    // cout << "\ndMonths: " << dMonths;
    // cout << "\nremDays: " << remDays;

    return yDays + bMDays + dMonths + getLeapDays(d2);
  }
  int getLeapDays(Date &d2) {
    int leaps = 0;

    if (mm > 2 && ((yy % 4 == 0 && yy % 100) || yy % 400 == 0))
      leaps++;

    for (int i = yy; i <= d2.yy; i++) {
      if ((i % 4 == 0 && i % 100) || i % 400 == 0)
        leaps++;
      if (i == d2.yy && d2.mm > 2)
        leaps++;
    }

    return leaps;
  }
};

int calcLife(float &lifeExpectancy) {
  int leaps = lifeExpectancy / 4;
  int days = lifeExpectancy * 365 + leaps;
  // cout << "\n" << days;
  return days;
}

// void saveImageAsPng(ofstream &img) {
//   string s;
//   cout << "\nSpecify a name for the image:\t";
//   cin >> s;
//   system("convert img s; echo 'yoyoyoy'");
// }

void createPPM(ofstream &img, int row, int col, int lineSep, int x, int totX) {
  for (int i = 0, k = 0; i < row; i++) {

    if (i % lineSep == 0) { // double blank line at line separation(decades etc)
      for (int j = 0; j < col; j++) {
        img << 0 << " " << 0 << " " << 0 << " ";
        img << 0 << " " << 0 << " " << 0 << " ";
      }
      img << 0 << " " << 0 << " " << 0 << "\n";
    }

    img << 0 << " " << 0 << " " << 0 << " "; // blankchar at first char

    for (int j = 0; j < col; j++) { // actual cells
      if (k++ < x)
        img << 160 << " " << 0 << " " << 0 << " "; // red for lived
      else {
        if (i >= 65)
          img << 128 << " " << 128 << " " << 128 << " "; // gray if >65
        else
          img << 0 << " " << 160 << " " << 0 << " "; // green for remaining
      }
      img << 0 << " " << 0 << " " << 0 << " "; // blankchar after every pixel
      if (j + 1 == col)
        cout << "\n"; // newline after every line
    }

    for (int j = 0; j < col; j++) { // blankline after every line
      img << 0 << " " << 0 << " " << 0 << " ";
      img << 0 << " " << 0 << " " << 0 << " ";
    }

    img << 0 << " " << 0 << " " << 0 << "\n";

    if (i * col >= totX)
      break;
  }
  // char c;
  // cout << "\nSave as png?(y/N):\t";
  // cin >> c;
  // if (c == 'y')
  //   saveImageAsPng(img);
}

void displayByDays(int &days, int &totDays, string fileName) {
  // cout << "\n" << days;

  int col = 365;
  int row = totDays / col + 1;
  int lineSep = 10;

  int width = col * 2 + 1; // left and right border
  int height =
      row * 2 + 1 +
      ((totDays / 365) / lineSep); // above and below border with separation

  fileName += "days";
  ofstream img;
  img.open(fileName + ".ppm");
  img << "P3" << endl << width << " " << height << "\n255\n";

  createPPM(img, row, col, lineSep, days, totDays);
}

// int r=160, g=160, b=160;
// cout << 160 << " " << 160 << " " << 160;
// cout << 0 << " " << 160 << " " << 0;

void displayByWeeks(int &days, int &totDays, string fileName) {
  int weeks = days / 7;
  int totWeeks = totDays / 7;
  // for (int i;;) {
  int col = 52;
  int row = totWeeks / col + 1;
  int lineSep = 5;

  int width = col * 2 + 1; // left and right border
  int height =
      row * 2 + 1 +
      ((totWeeks / col) / lineSep); // above and below border with separation

  fileName += "weeks";
  ofstream img;
  img.open(fileName + ".ppm");
  img << "P3" << endl << width << " " << height << "\n255\n";

  createPPM(img, row, col, lineSep, weeks, totWeeks);
}

void displayByYears(int &days, int &totDays) {
  int years = days / 365;
  int totYears = totDays / 365;
  // cout << "\n" << years << " " << totYears << "\n";
  int col = 11;
  for (; col > 7; col--)
    if (totYears % col == 0)
      break;

  int k = 0;
  int row = totYears / col + 1;
  cout << "\n\n\n";
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (k < years)
        cout << "X";
      else
        cout << "-";
      k++;
      if (i * col + j >= totYears)
        return;
    }
    cout << "\n";
  }
  cout << "\n\n\n";
}

int main() {
  // ios_base::sync_with_stdio(0);
  // cin.tie(0);
  time_t t = time(0);
  tm *now = localtime(&t);
  int n_year = now->tm_year + 1900;
  int n_mon = now->tm_mon + 1;
  int n_date = now->tm_mday;

  Date d1, d2;
  d1.inputDate();
  d2.setDate(n_year, n_mon, n_date);

  // d2.setDate(2025, 1, 1);

  bool check1 = d1.verifyDob(d2);
  if (check1) {
    cerr << "\nInvalid Date";
    return -1;
  }

  int days = d1.calcDays(d2);
  float le = 72.5;
  int remDays = calcLife(le);

  string fileName = d1.getDate();

  char c;
  cout << "\n";
  while (1) {
    cout << "\n1. Display by days";
    cout << "\n2. Display by weeks";
    cout << "\n3. Display by years";
    cout << "\n4. Exit";
    cout << "\nSelect display method:\t";
    cin >> c;
    switch (c) {
    case '1':
      displayByDays(days, remDays, fileName);
      break;
    case '2':
      displayByWeeks(days, remDays, fileName);
      break;
    case '3':
      displayByYears(days, remDays);
      break;
    case '4':
      exit(0);
      break;
    default:
      cout << "Please choose a valid option";
      break;
    }
  }

  // int age;
  // age = calculateAge();
  // cout << age;

  // cerr << "\n\n\ntime taken : " << (float)clock() / CLOCKS_PER_SEC << "
  // secs"
  // << endl;
  return 0;
}
