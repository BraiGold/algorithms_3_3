% Procesado de los datos
[n_cografo_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp2.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

% COMPLEJIDAD O(N* (N^2+n^3)) N=nodos cografo, n =nodos grafo completo
n = size(n_cografo_x); 
ult = n_cografo_x(n);
ultimo = ult(1);
primero = n_cografo_x(1);

dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-

n_vec = (primero:ult);


complejidad=times(times(n_vec,times(n_vec,n_vec))+times(n_vec,n_vec),n_vec);

complejidad_por_constante=times(complejidad,1/190000000);

hold on;
%x = gca;
%xlim([0 dim]);
%ylim([0.0005 0.0022]);
plot(n_vec,complejidad_por_constante,'r');  %complejidad
errorbar(n_cografo_x, tiempo_y, e, 'b');
xlabel('Cantidad de Nodos del cografo','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O(N* (N^2+n^3))','Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp2', filetype);