% Procesado de los datos
[m_x_t1, tiempo_y_t1, e_t1, cant_t1] = leer_datos_float('tiempos-exp1-tipo1.txt');
[m_x_t2, tiempo_y_t2, e_t2, cant_t2] = leer_datos_float('tiempos-exp1-tipo2.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
m1 = size(m_x_t1); 
ult = m_x_t1(m1);
ultimo = ult(1);
primero = m_x_t1(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n1_vec(1:dim)=100;
t=10; %TAMTABU
m1_vec = (primero:ult);
n2_vec(1:dim)=100; 
m2_vec(1:dim)=1000;
k=10;



complejidad=times(times(times(times(n1_vec+m1_vec,m2_vec),n1_vec)+times(n1_vec,log2(t))+t,k),m1_vec); %M1 es el minimo

complejidad_por_constante=times(complejidad,1/700000000);

hold on;
%x = gca;
xlim([0 215]);
%ylim([0.0005 0.0022]);
h=plot(m1_vec,complejidad_por_constante,'r');  %complejidad
errorbar(m_x_t1, tiempo_y_t1, e_t1, 'b');
errorbar(m_x_t2, tiempo_y_t2, e_t2, 'g');
xlabel('m','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O( ((n1+m1) x m2 x n1 + n1 x log(t) + t) x K x m1 )','Tipo 1','Tipo 2','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1', filetype);