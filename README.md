# Лабораторная работа №2 "Решение краевых задач для ОДУ"

## Цель работы 
Освоение методов численного решения краевых задач на примере первой краевой задачи для обыкновенного дифференциального уравнения (ОДУ) второго порядка с разрывными коэффициентами. Разработка, отладка и применение программных средств. Анализ сходимости и погрешности.

## Постановка задачи
*Основная задача* имеет вид:

$$ \frac{d}{dx} \left( k(x)\frac{du}{dx} \right) - q(x)u(x) = -f(x), \quad x \in (0, 1) $$

$$ k(x) \ge c_1 > 0, \quad q(x) \ge 0, \quad u(0)=\mu_1, \quad u(1) = \mu_2. $$

Коэффициенты $k(x)$, $q(x)$, $f(x)$ имеют разрыв в точке $\xi \in (0, 1)$ и заданы формулами вида
