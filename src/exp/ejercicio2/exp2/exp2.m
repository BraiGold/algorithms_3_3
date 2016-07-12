% Procesado de los datos
[planetas_x, tiempo_y, e, cant] = leer_datos_float('tiempos-exp1.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

m = 1000; %CANTIDAD DE ARISTAS CONSTANTE	

n = size(planetas_x);
ult = planetas_x(n);
ultimo = ult(1);
primero = planetas_x(1);

%disp(primero);
%disp(ultimo);

% COMPLEJIDAD O(m + n + n log m)


dim = ultimo-primero+1; %+1 porque matlab no me cuenta el cero -.-
%disp(dim);


eje_x = (primero:ult);
%disp('x');
%disp(eje_x);

auxm(1:dim) = m;
disp('M:');
disp(m);

auxlog = log2(auxm);
disp('log');
disp(auxlog);

aux_y = (auxm + eje_x + times(eje_x, auxlog));
disp(aux_y);
eje_y = times(aux_y, 1/4000000) 

%eje_y(1:dim) = (log2(m) * m) *(1/5000000);
disp('y');

hold on;
x = gca;
xlim([0 dim]);
%ylim([0.0005 0.0022]);
plot(eje_x,eje_y,'r'); 
errorbar(planetas_x, tiempo_y, e, 'b');
xlabel('Cantidad de Planetas','FontSize',12); %CAMBIAR M
ylabel('Tiempo de ejecucion en segundos','FontSize',10);
legend('Complejidad O(n + m + n log m)','Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp1', filetype);