% Procesado de los datos
[n_x_t1, tiempo_y_t1, e_t1, cant_t1] = leer_datos_float('tiempos-exp3-tipo1.txt');
[n_x_t2, tiempo_y_t2, e_t2, cant_t2] = leer_datos_float('tiempos-exp3-tipo2.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
%n = size(n_x_t1); 
%ult = n_x_t1(n);
%ultimo = ult(1);
%primero = n_x_t1(1);

%dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n
n_vec=n_x_t1;

%=============================calculo m = n * 3
m_vec = times(n_vec,3);
k=10;
t=10;

complejidad=times(times(times(times(n_vec+m_vec,m_vec),n_vec)+times(n_vec,log2(t))+t,k),m_vec); %M es el minimo

complejidad_por_constante=times(complejidad,1/5000000);

hold on;
x = gca;
xlim([10 25]);
%ylim([0 0.5]);
h=plot(n_vec,complejidad_por_constante,'r');  %complejidad
errorbar(n_x_t1, tiempo_y_t1, e_t1, 'b');
errorbar(n_x_t2, tiempo_y_t2, e_t2, 'g');
xlabel('n','FontSize',14); 
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O( ((n+m) x m x n + n x log(t) + t) x K x m )','Tipo 1','Tipo 2','Location','northwest')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp3', filetype);