% Procesado de los datos
[n1_x_f3_t1, tiempo_y_f3_t1, e_f3_t1, cant_f3_t1] = leer_datos_float('aristas-exp4-f3-tipo1.txt');
[n1_x_f4_t1, tiempo_y_f4_t1, e_f4_t1, cant_f4_t1] = leer_datos_float('aristas-exp4-f4-tipo1.txt');
[n1_x_f3_t2, tiempo_y_f3_t2, e_f3_t2, cant_f3_t2] = leer_datos_float('aristas-exp4-f3-tipo2.txt');
[n1_x_f4_t2, tiempo_y_f4_t2, e_f4_t2, cant_f4_t2] = leer_datos_float('aristas-exp4-f4-tipo2.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O( (n1+m1) x m2 x n1 x min{m1,m2} + n2 x log(n2) )
n1 = size(n1_x_f3_t1); 
ult = n1_x_f3_t1(n1);
ultimo = ult(1);
primero = n1_x_f3_t1(1);
dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo m1 = 3 x n1 //TOMO F3
m1=times(n1_vec,3);

%=============================calculo m1
n1_vec = (primero:ult);

%=============================calculo n2 = 300 Y m2 = 2500
n2_vec(1:dim)=300; 
m2_vec(1:dim)=2500;

complejidad=times(times(times(n1_vec+m1_vec,m2),n1),MINIMO)+times(n2_vec,log2(n2_vec));

complejidad_por_constante=times(complejidad,1/1600000000);

hold on;
x = gca;
xlim([0 dim]);
%ylim([0.0005 0.0022]);
h=plot(n1_vec,complejidad_por_constante,'c');  %complejidad
errorbar(n1_x_f3_t1, tiempo_y_f3_t1, e_f3_t1, 'b');
errorbar(n1_x_f4_t1, tiempo_y_f4_t1, e_f4_t1, 'g');
errorbar(n1_x_f3_t2, tiempo_y_f3_t2, e_f3_t2, 'r');
errorbar(n1_x_f4_t2, tiempo_y_f4_t2, e_f4_t2, 'm');
xlabel('m','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
legend('Complejidad O( (n1+m1) x m2 x n1 x min{m1,m2} + n2 x log(n2) )','F3 - Tipo1','F4 - Tipo1','F3 - Tipo2','F4 - Tipo2','Location','southeast')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4tiempos', filetype);