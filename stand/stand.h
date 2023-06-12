#ifndef STAND_H
#define STAND_H
//#include <QElapsedTimer>
#include <QString>

/* Класс для представления времени */
class MyTimer
{
public:
  // Текущее значение времени МИЛЛИсекунд
  // По умолчанию всегда 0
  unsigned long val = 0;
  // шаг дискретизации МИЛЛИсекунд
  // Нам понадобился именно шаг класс таймера, чтобы хранить
  // значение шага, который после влияет на сам сигнал
  // unsigned long delta;
  //QElapsedTimer qtimer;
  /*Конструктор класса*/
  MyTimer();
  /* Запуск таймера */
  //void start();
  /* Обновление таймера */
  void update();
};

/* Класс представляет собой Интегратор */
class Integrator
{
public:
  // сумма входящих сигналов - значение интеграла
  double s = 0;
  // Шаг дискретизации
  unsigned long T = 10;
  // Последнее сохранённое время
  unsigned long t_before = 0;

  /* ПУСТОЙ Конструктор класса */
  // Вызывается, когда пишем
  // Integrator integ() - создаём новый объект, без заданных смещений
  Integrator();
  /* Конструктор класса со СМЕЩЕНИЯМИ */
  // Вызывается, когда пишем
  // Integrator integ(1) - создаём новый объект, c заданными отклонениями c_s
  Integrator(double c_s);
  /* Подаём на вход сигнал */
  // u - значение сигнала на входе в интегратор
  void in(double in_u, MyTimer &timer);
  /* Выходная линия с интеграла */
  double out();
};

/*Класс Множителя, умножает сигнал на какое-то число*/
class Gain
{
public:
  // Множитель, по умолчанию = 1, то есть не изменяет сигнал
  double multiplier = 1;
  // Преобразованный сигнал по умолчанию 0
  double u = 0;
  Gain();
  /*Конструктор множителя*/
  Gain(double m);
  /* На входе подаем значение сигнала */
  void in(double in_u);
  /* Выходная линия множителя */
  double out();
};

/* Класс отклонения (сумматор с константой) */
class Deviation
{
public:
  // Значение сигнала, полученного Сумматором
  double u = 0;
  double dev = 0.001;
  Deviation();
  Deviation(double def_dev);
  /* На входе подаём сигнал */
  void in(double u_in);
  /* Выходная линия с сумматора */
  double out();
};

/* Класс испытательного стенда на компьютере */
class Stand
{
public:
  // имеет свой таймер
  MyTimer timer;
  // Множитель
  Gain gain;
  // Отклонение (возмущение)
  Deviation dev;
  // Интеграл скорости
  Integrator speed;
  // Интеграл угла
  Integrator angle;
  /*Конструктор класса*/
  Stand();
  // Что делаем на запуске стенда
  void start();
  // Что обрабатываем на входе
  void in(QString data);
  // Тот же in только для значения сигнала
  // а не строки котрую надо обрабатывать
  void run(double u_i);
  // На выходе получаем строку с параметрами
  QString out();

};

#endif // STAND_H
