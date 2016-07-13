% Procesado de los datos
[n_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp3.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O((n1+m1) x m2 + n2 x log(n2) )
n = size(n_x); 
ult = n_x(n);
ultimo = ult(1);
primero = n_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n
n_vec=n_x;

%=============================calculo m = n * 3
m_vec = times(n_vec,3);

%======= calculo N1+M1
complejidad=times(n_vec+m_vec,m_vec)+times(log2(n_vec),n_vec);

complejidad_por_constante=times(complejidad,1/8000000);

%======= calculo N1+M1
%aux1=n_vec+m_vec;

%======= calculo (n1+m1) x m2
%aux2=times(aux1,m_vec);

%======= calculo log(n2)
%aux3=log2(n_vec);

%======= calculo log(n2) x n2
%aux4=times(aux3,n_vec);

%complejidad=aux2+aux4;

%complejidad_por_constante=times(complejidad,1/8000000);

hold on;
x = gca;
xlim([primero dim]);
%ylim([0.0005 0.0022]);
h=plot(n_vec,complejidad_por_constante,'r');  %complejidad
errorbar(n_x, tiempo_y, e, 'b');
xlabel('n','FontSize',14); 
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O((n1+m1) x m2 + n2 x log(n2))','Tiempo de ejecucion del algoritmo','Location','northwest')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp3', filetype);