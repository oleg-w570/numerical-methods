# Лабораторная работа №1 "Численное решение задачи Коши для ОДУ"

## Цель работы

Целью данной лабораторной работы является освоение одношаговых методов численного интегрирования задачи Коши для ОДУ с элементами оценки погрешности на шаге и управления шагом.

## Постановка задачи

*Тестовая* задача имеет вид:

$$
\begin{cases}
    \frac{du}{dx} = -\frac{3}{2}u, \\
    u(0) = u_0.
\end{cases}
$$

*Основная* задача *№1* имеет вид:

$$
\begin{cases}
    \frac{du}{dx} = \frac{u^2}{(1+x^2)^{1/3}} + u - u^3\sin(10x),\\
    u(0) = u_0.
\end{cases}
$$

*Основная* задача *№2* имеет вид:

$$
    \begin{cases}
        \frac{d^2u}{dx^2} + a(u')^2 + bu = 0,\\
        u(0) = u_0, \\
        u'(0) =  u'_0.
    \end{cases}
$$

Решение тестовой и основных задач будет производится, используя метод Рунге-Кутта 4-го порядка.  

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


# Лабораторная работа №3 "Построение интерполирующего кубического сплайна"

Программа для построения, визуализации и анализа кубических сплайнов $S(x)$, интерполирующих функции $F(x)$ при следующих условиях:

1. тестовая функция $F(x) = \varphi(x)$, заданная формулой

$$
\varphi =
\begin{cases}
    x^3+3x^2, \quad x \in [-1, 0]\\
    -x^3+3x^2, \quad x \in [0, 1]
\end{cases}
$$

на отрезке $x \in [-1, 1]$, сетка равномерная, граничные условия

$$
S''(-1) = \varphi''(-1) = 0, \quad S''(1) = \varphi''(1) = 0
$$

(совпадение вторых производных);

2. основную функцию F(x) = f(x), где

$$
f(x) = \frac{\ln(x+1)}{x+1}
$$

на отрезке $x \in [a, b]$, сетка равномерная, граничные условия

$$
S''(a) = S''(b) = 0
$$

(естественные граничные условия);

3. осциллирующую функцию $F(x) = f(x) + \cos(10x)$ при тех же $x \in [a, b]$, сетка равномерная, естественные граничные условия.

Размерность сетки, то есть число участков $n$, является параметром программы.


# Лабораторная работа №4 "Решение задачи Дирихле для уравнения Пуассона (итерационный метод и его реализация в нестандартной области)"

## Цель работы

Решение разностных схем итерационными методами, расчет параметров метода, его программная реализация в области нестандартной геометрии. Проверка сходимости, оценка погрешности и ее компонент. Решение тестовой модельной задачи с заданной погрешностью.

## Постановка задачи

Рассматривается задача Дирихле для уравнения Пуассона в некоторой области $G$, вписанной вместе со своей границей в прямоугольник $[a, b]⊗[c, d]$.
Задача записывается в виде

$$
Δu(x, y) = –f(x, y) \text{ при } (x, y)∈ G, G⊂[a, b]⊗[c, d],
$$

$$
u(x, y) = μ(x, y) \text{ при } (x, y) ∈ dG.
$$

Значения $a=-1$, $b=1$, $c=-1$, $d=1$. Необходимо найти решение задачи – функцию $u(x, y)$, заданную на множестве $G ∪ dG$.

Чтобы построить тестовую задачу, рассмотрим функцию $u(x,y)=e^{1-x^2-y^2}$. Затем подберите такие $f(x, y)$ и $μ(x, y)$,
чтобы $u(x, y)$ являлась решением задачи при $(x, y) ∈ G ∪ dG$. Очевидно, значения $μ(x, y)$ и $u(x, y)$ на границе области должны совпадать, то есть $μ(x, y) = u(x, y)$
при $(x, y)∈dG$.

С помощью итерационного метода с чебышевским набором параметров задачу нужно решить численно с заданной погрешностью.


# Нестационарное уравнение теплопроводности

Уравнение теплопроводности на отрезке $x ∈ [0, 1]$ для отрезка по времени $t \in [0, 100]$ имеет вид:

$$
    \begin{cases}
        u'_t = 5u''_{xx} + \sin t, \\
        u(x, 0) = 1 - x^2, \\
        u(0, t) = \cos t, \\
        u(1, t) = \sin 4t.
    \end{cases}
$$

Нужно найти функцию $u(x, t)$ - решение уравнения. \
Решение ищем численно с помощью построения неявной схемы с весом $0,5$. 