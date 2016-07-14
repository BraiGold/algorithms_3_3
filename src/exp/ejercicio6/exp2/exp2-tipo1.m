
% Procesado de los datos
[n_x_f1, tiempo_y_f1, e_f1, cant_f1] = leer_datos_float('tiempos-exp2-f1-tipo1.txt');
[n_x_f2, tiempo_y_f2, e_f2, cant_f2] = leer_datos_float('tiempos-exp2-f2-tipo1.txt');
[n_x_f3, tiempo_y_f3, e_f3, cant_f3] = leer_datos_float('tiempos-exp2-f3-tipo1.txt');
[n_x_f4, tiempo_y_f4, e_f4, cant_f4] = leer_datos_float('tiempos-exp2-f4-tipo1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD $\mathcal{O}(((n_1+m_1)*m_2*n_1+n_1*log(t)+t)*K* min\{m_1,m_2\})$
n1 = size(n_x_f1); %son todos del mismo tamaño
ult = n_x_f1(n1);
ultimo = ult(1);
primero = n_x_f1(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n1_vec=(primero:ult);
t=10
k=10
n2_vec(1:dim)=50; 
m2_vec(1:dim)=30;
m1_vec=n1_vec-1; % TOMO M1=N-1 

complejidad=times(times(times(times(n1_vec+m1_vec,m2_vec),n1_vec)+times(n1_vec,log2(t))+t,k),m1_vec); %M1 es el minimo


complejidad_por_constante=times(complejidad,1/600000);

hold on;
x = gca;
xlim([primero dim]);
ylim([0 10]);
h=plot(n1_vec,complejidad_por_constante,'c');  %grafico la complejidad
errorbar(n_x_f1, tiempo_y_f1, e_f1, 'b');
errorbar(n_x_f2, tiempo_y_f2, e_f2, 'r');
errorbar(n_x_f3, tiempo_y_f3, e_f3, 'g');
errorbar(n_x_f4, tiempo_y_f4, e_f4, 'm');
xlabel('n1','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O( ((n1+m1) x m2 x n1 + n1 x log(t) + t) x K x m1 )','F1','F2','F3','F4','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log'); %esto es para la escala logaritmica
hold off;
print('exp2-tipo1', filetype);