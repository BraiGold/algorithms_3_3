% Procesado de los datos
[m_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O(n2^n1 x (n1+m1) x m2)
m1 = size(m_x); %son todos del mismo tamaño
ult = m_x(m1);
ultimo = ult(1);
primero = m_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1 = 8
n1_vec(1:dim)=8;
disp('N1:');
disp(n1_vec);

%=============================calculo m1
m1_vec = (primero:ult);
disp('M1:');
disp(m1_vec);


%=============================calculo n2 = 6 Y m2 = 10
n2_vec(1:dim)=8; 
disp('N2:');
disp(n2_vec);
m2_vec(1:dim)=17;
disp('M2:');
disp(m2_vec);

%======= calculo N1+M1
aux1=n1_vec+m1_vec;
disp('N1 + M1');
disp(aux1);


%======= calculo N2^N1
%for i=1:dim
%      aux2=n2_vec.^n1_vec(i)
%end
aux2=power(n2_vec,n1_vec);
disp('N2^N1 : ');
disp(aux2);

aux3=times(aux2,aux1);
complejidad=times(aux3,m2_vec);

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