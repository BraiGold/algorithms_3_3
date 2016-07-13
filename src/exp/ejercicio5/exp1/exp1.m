% Procesado de los datos
[m_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O( (n1+m1) x m2 x n1 x min{m1,m2} + n2 x log(n2) )
m1 = size(m_x); 
ult = m_x(m1);
ultimo = ult(1);
primero = m_x(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1 = 200
n1_vec(1:dim)=200;

%=============================calculo m1
m1_vec = (primero:ult);

%=============================calculo n2 = 200 Y m2 = 2500
n2_vec(1:dim)=200; 
m2_vec(1:dim)=2500;

complejidad=times(times(times(n1_vec+m1_vec,m2_vec),n1_vec),MINIMO)+times(n2_vec,log2(n2_vec));

complejidad_por_constante=times(complejidad,1/1600000000);

hold on;
x = gca;
xlim([0 dim]);
%ylim([0.0005 0.0022]);
h=plot(m1_vec,complejidad_por_constante,'r');  %complejidad
errorbar(m_x, tiempo_y, e, 'b');
xlabel('m','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O((n2^n1) x (n1+m1) x m2)','Tiempo de ejecucion del algoritmo','Location','southeast')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1', filetype);