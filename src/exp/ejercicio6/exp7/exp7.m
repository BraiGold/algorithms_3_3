% Procesado de los datos
[k_x_aristas, y_aristas, e_aristas, cant_aristas] = leer_datos_float('aristas-exp7.txt');
[k_x_t, tiempo_y_t, e_t, cant_t] = leer_datos_float('tiempos-exp7.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
CM = size(k_x_t); 
ult = k_x_t(CM);
ultimo = ult(1);
primero = k_x_t(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n_vec=50;
m_vec=200;
k_vec=(primero:ultimo);
t=20;
complejidad=times(times(times(times(n_vec+m_vec,m_vec),n_vec)+times(n_vec,log2(t))+t,k_vec),m_vec); %M1 es el minimo

complejidad_por_constante=times(complejidad,1/1800000000);

hold on;
%x = gca;
xlim([5 25]);
%ylim([0 5]);
h=plot(k_vec,complejidad_por_constante,'r');  %complejidad
errorbar(k_x_t, tiempo_y_t, e_t, 'b');
xlabel('k','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O( ((n1+m1) x m2 x n1 + n1 x log(t) + t) x K x m1 )','Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp7-tiempos', filetype);

figure;

hold on;
%x = gca;
%xlim([0 dim]);
%ylim([0 80]);
stem(k_x_aristas, y_aristas, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
xlabel('k','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp7-aristas', filetype);