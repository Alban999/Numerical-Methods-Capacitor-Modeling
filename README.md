# Numerical-Methods-Capacitor-Modelisation

We consider the problem of determining the electrostatic potential in a capacitor. The capacitor considered has the shape of a rectangular parallelepiped (shape of a box) whose section by the plane $z=z_0$ for every $z_0\, \int\, [0,Lz]$ is represented below. In this diagram, the envelope of the capacitor (colored in shades of blue) corresponds to a set of four supposedly perfect and mutually insulated conductors, while the heart of the capacitor (in yellow) is filled with a dielectric of permittivity $\epsilon$.

![schema](https://drive.google.com/file/d/1Nf-d57CG-hDV3W8QoqXbgZaqV45tVjnq/view?usp=drive_link)

The mathematical modeling of the problem can be done in two dimensions. This is due to the geometry of the capacitor, which is translationally invariant in the direction $z$, but also because we assume, here and in the sequel, that the length $L_z$ of the capacitor is sufficiently large so that the dependence of the electric potential on the variable $z$ can be neglected. The problem is then formulated as follows: determine the electric potential $u(x, y)$ for everything $(x, y)\, \int\, \Omega$ such that

$$
\begin{equation}
    \begin{cases}
      -\frac{d^2 u}{dx^2} -\frac{d^2 u}{dy^2} = \frac{\rho}{\epsilon} \; \text{on}\; \Omega\, \int \, 	\mathbb{R}^2\\
      boundary conditions\; \text{on}\; \delta \Omega
    \end{cases}
\end{equation}
$$

where $\Omega$ corresponds to the interior of the capacitor, as schematized in the figure above, $\rho$ is the electric charge distribution in $\Omega$, and $\epsilon$ is the electrical permittivity of the dielectric inside $\Omega$. For a capacitor we typically have $\rho = 0$.

Regarding the boundary conditions, we note that the value of the electric potential $u$ must be identical inside each conductor (perfect conductors are considered), but it can vary from one conductor to another. In particular, in our case the domain is surrounded by four conductors: upper terminal of the capacitor ($\Gamma_t$), lower bound ($\Gamma_b$), and the two conductors of the electrical enclosure ($\Gamma_e$). The values of the potential of these conductors – $u_t$, $u_b$ and $u_e$ – are imposed as boundary conditions. The boundary conditions are therefore

$u = u_t$ on $\Gamma_t$, $u = u_b$ on $\Gamma_b$ and $u = u_e$ on $\Gamma_e$

Let us now talked about the discretization. We consider a capacitor in the form of a rectangular parallelepiped (shape of a box) whose interior $\Omega$ of the section by a plane $z=z_0$ is a rectangle $L_x \times L_y$. The discretization approach is illustrated here in the simple case where $\Omega$ has the shape of a square $L\times L$; see figure below.

In the case of a square section, we propose to determine an approximation of the electric potential $u$ at grid points

$(x_i, y_j) = (ih, jh)$, $i,j=1,...,m-2$

Where m is the number of grid points aligned in one direction, and $h=\frac{L}{m-1}$ is the discretization step. These points uniformly cover the interior of the square domain, but not the edge of it, where the potential is known.

![discretization](https://drive.google.com/file/d/1_GRdZhQuAOfLUsO87Z3kMcj0VNCh35Eo/view?usp=drive_link)

To each point of the grid we associate an approximation $u_{i,j}$ electric potential at the point $(x_i, y_j)$ . For each point, we also establish in what follows a linear equation in the variables $u_{i,j}$ ; all of these equations form a linear system. To obtain these equations we use in particular the centered difference formula for the second derivative which, for a function $u$ in function of the variable $x$, corresponds to

$$\frac{d^2 u}{dx^2} \simeq \frac{u(x-h) - 2u(x) + u(x+h)}{h^2}$$

The equation for a point $(x_i, y_j)$ of the discretization grid, $1\le i, j\le m−2$, is obtained using the approximation above in the partial differential equation (the first equation) of system of equations above for the partial derivative according to $x$ and for the one according to $y$ here, which give

$$-\frac{u_{i-1,j} - 2u_{i,j} + u_{i+1,j}}{h^2}-\frac{u_{i,j-1} - 2u_{i,j} + u_{i,j+1}}{h^2} = \frac{\rho(x_i, y_j)}{\epsilon}$$

where, as a reminder, $u_{i,j}$ represents the approximation of the solution $u$ on point $(x_i, y_j)$.

By grouping all the equations thus derived, we obtain the following linear system

$$Au = b$$

that we solve to determine the approximation $u$ of the electric potential.

