% Procesado de los datos
[m_x_t1, tiempo_y_t1, e_t1, cant_t1] = leer_datos_float('tiempos-exp1-tipo1.txt');
[m_x_t2, tiempo_y_t2, e_t2, cant_t2] = leer_datos_float('tiempos-exp1-tipo2.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O( (n1+m1) x m2 x n1 x m1 + n2 x log(n2) ) 
m1 = size(m_x_t1); 
ult = m_x_t1(m1);
ultimo = ult(1);
primero = m_x_t1(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1 = 150
n1_vec(1:dim)=150;

%=============================calculo m1
m1_vec = (primero:ult);

%=============================calculo n2 = 150 Y m2 = 200
n2_vec(1:dim)=150; 
m2_vec(1:dim)=200;

complejidad=times(times(times(n1_vec+m1_vec,m2_vec),n1_vec),m1_vec)+times(n2_vec,log2(n2_vec));

complejidad_por_constante=times(complejidad,1/800000000);

hold on;
x = gca;
xlim([0 200]);
ylim([0 4]);
plot(m1_vec,complejidad_por_constante,'r');  %complejidad
errorbar(m_x_t1, tiempo_y_t1, e_t1, 'b');
errorbar(m_x_t2, tiempo_y_t2, e_t2, 'g');
xlabel('m','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O( (n1+m1) x m2 x n1 x m1 + n2 x log(n2) ) ','Tipo 1','Tipo 2','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1', filetype);