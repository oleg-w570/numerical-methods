# Лабораторная работа №2 "Решение краевых задач для ОДУ"

**Вариант 3.** $\xi = 0.3$, $\mu_1 = 1$, $\mu_2 = 0$, $k_1(x) = x^2 + 2$, $k_2(x) = x^2$, $q_1(x) = x$, $q_2(x) = x^2$, $f_1(x) = 1$, $f_2(x) = \sin(\pi x)$. 

## Цель работы

Освоение методов численного решения краевых задач на примере первой краевой задачи для обыкновенного дифференциального уравнения (ОДУ) второго порядка с разрывными коэффициентами. Разработка, отладка и применение программных средств. Анализ сходимости и погрешности.

## Постановка задачи

*Основная задача* имеет вид:

$$
\frac{d}{dx} \left( k(x)\frac{du}{dx} \right) - q(x)u(x) = -f(x), \quad x \in (0, 1) 
$$

$$ 
k(x) \ge c_1 > 0, \quad q(x) \ge 0, \quad u(0)=\mu_1, \quad u(1) = \mu_2.
$$

Коэффициенты $k(x)$, $q(x)$, $f(x)$ имеют разрыв в точке $\xi \in (0, 1)$ и заданы формулами вида

$$
k(x) = k_1(x), \text{ при } x \in [0, \xi) \qquad k(x) = k_2(x), \text{ при } x \in (\xi, 1]
$$

$$
q(x) = q_1(x), \text{ при } x \in [0, \xi) \qquad q(x) = q_2(x), \text{ при } x \in (\xi, 1]
$$

$$
f(x) = f_1(x), \text{ при } x \in [0, \xi) \qquad f(x) = f_2(x), \text{ при } x \in (\xi, 1]
$$

Решением задачи является функция $u(x)$, непрерывная по $x$ при
$x ∈ [0, 1]$, такая, что функция теплового потока

$$
w(x) = – k(x) \frac{du}{dx}
$$

при $x ∈ [0, 1]$ также является непрерывной.

