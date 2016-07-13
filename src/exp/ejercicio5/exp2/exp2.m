% Procesado de los datos
[n_x_f1, tiempo_y_f1, e_f1, cant_f1] = leer_datos_float('tiempos-exp2-f1.txt');
[n_x_f2, tiempo_y_f2, e_f2, cant_f2] = leer_datos_float('tiempos-exp2-f2.txt');
[n_x_f3, tiempo_y_f3, e_f3, cant_f3] = leer_datos_float('tiempos-exp2-f3.txt');
[n_x_f4, tiempo_y_f4, e_f4, cant_f4] = leer_datos_float('tiempos-exp2-f4.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;


% COMPLEJIDAD O( (n1+n1-1) x m2 x n1 x min{n1-1,m2} + n2 x log(n2) ) REEMPLACE M1 POR N1-1
n1 = size(n_x_f1); %son todos del mismo tamaño
ult = n_x_f1(n1);
ultimo = ult(1);
primero = n_x_f1(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1
n1_vec=(primero:ult);

%=============================calculo n2 = 300 Y m2 = 2500
n2_vec(1:dim)=300; 
m2_vec(1:dim)=2500;

complejidad=times(times(times(n1_vec+m1_vec,m2_vec),n1_vec),MINIMO)+times(n2_vec,log2(n2_vec));

complejidad_por_constante=times(complejidad,1/100000);

hold on;
x = gca;
xlim([primero dim]);
%ylim([0.0005 0.0022]);
h=plot(n1_vec,complejidad_por_constante,'c');  complejidad
errorbar(n_x_f1, tiempo_y_f1, e_f1, 'b');
errorbar(n_x_f2, tiempo_y_f2, e_f2, 'r');
errorbar(n_x_f3, tiempo_y_f3, e_f3, 'g');
errorbar(n_x_f4, tiempo_y_f4, e_f4, 'm');
xlabel('n1','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('O((n1+n1-1) x m2 + n2 x log(n2))','F1','F2','F3','F4','Location','southeast')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp2', filetype);