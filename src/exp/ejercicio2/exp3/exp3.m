% Procesado de los datos
[n_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp3.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O(n2^n1 x (n1+m1) x m2)
n = size(n_x); 
ult = n_x(n);
ultimo = ult(1);
primero = n_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

%=============================calculo n
n_vec=n_x;
disp('N:');
disp(n_vec);

%=============================calculo m = n * 3
m_vec = times(n_vec,3);
disp('M:');
disp(m_vec);


%======= calculo N1+M1
aux1=n_vec+m_vec;
disp('N + M');
disp(aux1);


%======= calculo N2^N1 (N^N) (N1=N2)
%for i=1:dim
%      aux2=n2_vec.^n1_vec(i)
%end
aux2=power(n_vec,n_vec);
disp('N^N : ');
disp(aux2);

aux3=times(aux2,aux1);
complejidad=times(aux3,m_vec);

complejidad_por_constante=times(complejidad,1/80000000);

hold on;
x = gca;
xlim([primero dim]);
%ylim([0.0005 0.0022]);
h=plot(n_vec,complejidad_por_constante,'r');  %complejidad
errorbar(n_x, tiempo_y, e, 'b');
xlabel('n','FontSize',14); 
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O((n2^n1) x (n1+m1) x m2)','Tiempo de ejecucion del algoritmo','Location','northwest')
set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp3', filetype);