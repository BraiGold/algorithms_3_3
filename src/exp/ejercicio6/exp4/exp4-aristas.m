% Procesado de los datos
[n1_x_f3_t1, aristas_y_f3_t1, e_f3_t1, cant_f3_t1] = leer_datos_float('aristas-exp4-f3-tipo1.txt');
[n1_x_f4_t1, aristas_y_f4_t1, e_f4_t1, cant_f4_t1] = leer_datos_float('aristas-exp4-f4-tipo1.txt');
[n1_x_f3_t2, aristas_y_f3_t2, e_f3_t2, cant_f3_t2] = leer_datos_float('aristas-exp4-f3-tipo2.txt');
[n1_x_f4_t2, aristas_y_f4_t2, e_f4_t2, cant_f4_t2] = leer_datos_float('aristas-exp4-f4-tipo2.txt');

% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;

hold on;
%x = gca;
xlim([8 22]);
ylim([10 48]);
stem(n1_x_f3_t1, aristas_y_f3_t1, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
stem(n1_x_f3_t2, aristas_y_f3_t2, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'blue');
xlabel('n1','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
legend('Tipo1','Tipo2','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4aristas-f3', filetype);


figure;

hold on;
%x = gca;
%xlim([0 dim]);
%ylim([-0.2 1.2]);
stem(n1_x_f4_t1, aristas_y_f4_t1, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'red');
stem(n1_x_f4_t2, aristas_y_f4_t2, 'LineStyle', 'none', 'Marker', 'o', 'MarkerEdgeColor', 'blue');
xlabel('n1','FontSize',12); %CAMBIAR M
ylabel('Cantidad de aristas','FontSize',10);
legend('Tipo1','Tipo2','Location','northeast')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('exp4aristas-f4', filetype);