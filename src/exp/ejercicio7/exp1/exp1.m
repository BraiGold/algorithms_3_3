% Procesado de los datos
[m_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O((n1+m1) x m2 + n2 x log(n2) )
m1 = size(m_x); 
ult = m_x(m1);
ultimo = ult(1);
primero = m_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n1 = 200
n1_vec(1:dim)=200;
%disp('N1:');
%disp(n1_vec);

%=============================calculo m1
m1_vec = (primero:ult);
%disp('M1:');
%disp(m1_vec);


%=============================calculo n2 = 200 Y m2 = 2500
n2_vec(1:dim)=200; 
%disp('N2:');
%disp(n2_vec);
m2_vec(1:dim)=2500;
%disp('M2:');
%disp(m2_vec);

%======= calculo N1+M1
aux1=n1_vec+m1_vec;
%disp('N1 + M1');
%disp(aux1);

%======= calculo (N1+M1) x M2
aux2=times(aux1,m2_vec);
%disp('(N1+M1) x M2 : ');
%disp(aux2);

%======= calculo log(N2)
aux3=log2(n2_vec);
%disp('log(N2): ');
%disp(aux3);

%======= calculo N2 x log(N2) 
aux4=times(aux3, n2_vec)
%disp('N2 x log(N2): ');
%disp(aux4);

complejidad=aux2+aux4;

complejidad_por_constante=times(complejidad,1/25000000);

hold on;
x = gca;
xlim([0 dim]);
%ylim([0.0005 0.0022]);
plot(m1_vec,complejidad_por_constante,'r');  %complejidad
errorbar(m_x, tiempo_y, e, 'b');
xlabel('m','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O((n1+m1) x m2 + n2 x log2(n2))','Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1', filetype);