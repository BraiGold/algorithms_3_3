% Procesado de los datos
[tabu_x_aristas, y_aristas, e_aristas, cant_aristas] = leer_datos_float('aristas-exp5.txt');
[tabu_x_t, tiempo_y_t, e_t, cant_t] = leer_datos_float('tiempos-exp5.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
t = size(tabu_x_t); 
ult = tabu_x_t(t);
ultimo = ult(1);
primero = tabu_x_t(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n_vec=50;
m_vec=200;
k=10;
t_vec=tabu_x_t;
complejidad=times(times(times(times(n_vec+m_vec,m_vec),n_vec)+times(n_vec,log2(t_vec))+t_vec,k),m_vec); %M1 es el minimo

complejidad_por_constante=times(complejidad,1/2000000000);

hold on;
%x = gca;
xlim([5 30]);
%ylim([0 5]);
h=plot(t_vec,complejidad_por_constante,'r');  %complejidad
errorbar(tabu_x_t, tiempo_y_t, e_t, 'b');
xlabel('Tam. de lista tabu','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O( ((n1+m1) x m2 x n1 + n1 x log(t) + t) x K x m1 )','Tiempo de ejecucion del algoritmo','Location','northwest')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4-tiempos', filetype);

figure;

hold on;
%x = gca;
%xlim([0 dim]);
ylim([0 80]);
stem(tabu_x_aristas, y_aristas, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
xlabel('Tam. de lista tabu','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4-aristas', filetype);