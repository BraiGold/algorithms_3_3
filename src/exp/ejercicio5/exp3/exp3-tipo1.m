% Procesado de los datos
[n_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp3-tipo1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O( (n+m) x m x n x m + n x log(n) ) //como son iguales, el minimo es cualquiera
n = size(n_x); 
ult = n_x(n);
ultimo = ult(1);
primero = n_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n
n_vec=n_x;
disp('N:');
disp(n_vec);

%=============================calculo m = n * 3
m_vec = times(n_vec,3);
disp('M:');
disp(m_vec);

complejidad=times(times(times(n_vec+m_vec,m_vec),n_vec),m_vec)+times(n_vec,log2(n_vec));


complejidad_por_constante=times(complejidad,1/60000000);

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
print('exp3-tipo1', filetype);