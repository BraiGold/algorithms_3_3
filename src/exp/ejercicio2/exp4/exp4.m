% Procesado de los datos
[n_x_f3, tiempo_y_f3, e_f3, cant_f3] = leer_datos_float('tiempos-exp4-f3.txt');
[n_x_f4, tiempo_y_f4, e_f4, cant_f4] = leer_datos_float('tiempos-exp4-f4.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;


% COMPLEJIDAD O(n2^n1 x (n1+n1-1) x m2) REEMPLACE M1 POR N1-1
n1 = size(n_x_f3); %son todos del mismo tamaño
ult = n_x_f3(n1);
ultimo = ult(1);
primero = n_x_f3(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1
n1_vec=(primero:ult);
disp('N1:');
disp(n1_vec);

%=============================calculo n2 = 6 Y m2 = 10
n2_vec(1:dim)=6; 
disp('N2:');
disp(n2_vec);
m2_vec(1:dim)=10;
disp('M2:');
disp(m2_vec);

%======= calculo 3 * N1
aux1=times(n1_vec,3);
disp('3 * N1:');
disp(aux1);

%======= calculo N1+ 3 * N1
aux2=n1_vec+aux1;
disp('N1+ (3 * N1) : ');
disp(aux2);

%======= calculo N2^N1
%for i=1:dim
%      aux2=n2_vec.^n1_vec(i)
%end
aux3=power(n2_vec,n1_vec);
disp('N2^N1 : ');
disp(aux3);

aux4=times(aux2,aux3); %(N1+N1-1) x (N2^N1)
complejidad=times(aux4,m2_vec);

complejidad_por_constante=times(complejidad,1/50000000);

hold on;
x = gca;
xlim([primero dim]);
%ylim([0.0005 0.0022]);
h=plot(n1_vec,complejidad_por_constante,'c');  complejidad
errorbar(n_x_f3, tiempo_y_f3, e_f3, 'g');
errorbar(n_x_f4, tiempo_y_f4, e_f4, 'm');
xlabel('n1','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O((n2^n1) x (n1+(3*N1)) x m2)','F3','F4','Location','northwest')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4', filetype);