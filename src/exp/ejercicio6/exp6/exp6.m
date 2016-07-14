% Procesado de los datos
[cuantosMiro_x_aristas, y_aristas, e_aristas, cant_aristas] = leer_datos_float('aristas-exp6.txt');
[cuantosMiro_x_t, tiempo_y_t, e_t, cant_t] = leer_datos_float('tiempos-exp6.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
CM = size(cuantosMiro_x_t); 
ult = cuantosMiro_x_t(CM);
ultimo = ult(1);
primero = cuantosMiro_x_t(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n_vec=50;
m_vec=200;
k=10;
t=20;
complejidad=times(times(times(times(n_vec+m_vec,m_vec),n_vec)+times(n_vec,log2(t))+t,k),m_vec); %M1 es el minimo

complejidad_por_constante=times(complejidad,1/500000000);
complejidad_por_constante_vec(1:6)=complejidad_por_constante;

hold on;
%x = gca;
xlim([5 30]);
%ylim([0 5]);
%h=plot(cuantosMiro_x_t,complejidad_por_constante_vec,'r');  %complejidad
errorbar(cuantosMiro_x_t, tiempo_y_t, e_t, 'b');
xlabel('Cantidad de vecinos que toma cada iteracion','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp6-tiempos', filetype);

figure;

hold on;
%x = gca;
%xlim([0 dim]);
%ylim([0 80]);
stem(cuantosMiro_x_aristas, y_aristas, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
xlabel('Cantidad de vecinos que toma cada iteracion','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp6-aristas', filetype);