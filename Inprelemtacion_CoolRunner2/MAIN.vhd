library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Main is
    Port ( 
	   clock:in STD_LOGIC;
	   switches : in STD_LOGIC_VECTOR (1 downto 0);
		pin_switch : out STD_LOGIC_VECTOR (1 downto 0);
		botones : in STD_LOGIC_VECTOR (1 downto 0); 
		pin_boton : out STD_LOGIC_VECTOR (1 downto 0);
		pin_boton_entradas : in STD_LOGIC_VECTOR (1 downto 0);
		Display : out STD_LOGIC_VECTOR(6 downto 0);
	   ANODE : out STD_LOGIC_VECTOR(3 downto 0));
end Main;



architecture Behavioral of Main is


signal clock_divider : STD_LOGIC_VECTOR (12 downto 0);   --lo que divide clock para ralentizarlo
signal clock2 : STD_LOGIC;  --clock con la velocidad bajada
signal contador : STD_LOGIC_VECTOR(1 downto 0);  --el opcode(por decirlo así) de las funoiones del case

begin


process (clock)

begin

--la parte del clk2 hace un reset bal proccess de arriba

	if(rising_edge(clock)) then  --si clock cambia de 0 a 1 devuelve true
	
		if clock_divider="0000000000000" then   --si clock_divider es 0 entonces clock2 es 1, activva process(clock2)
			clock2 <= '1';
		else
			clock2<= '0';    --sino es 0
		end if;

		clock_divider <= clock_divider+"0000000000001";  --aunque la suma se efectue aquí el valor no cambia hasta que termina el process
		
		if clock_divider > "0000000001000" then -- si pasa de 1000 el clock_divider reinicia a 0, esto regula la velocidad del reset
			clock_divider<="0000000000000";
		end if;
		
	end if;
	
end process;

--los process se ejecutan en paralelo, es decir, cuando en process(clock) se cambie clock2 empezará a
--ejecutarse process(clock2) simultaneamente, sin más


process(clock2)

begin
if(rising_edge(clock2)) then
	contador <= contador + 1;
end if;

--Recordad, los proccess no cambian las señales hasta terminar cada ciclo del process, es decir,
--la primera vez que entremos aquí incluso después de sumar estaremos en case contador == 00

--Aquí en vez de un case se puede usar process(contador)
--luego en vez de when se podría usar with contador select
--Técnicamente hablando es otro process más

	case contador is   
		when "00" => 	
		
		--Los botones elegidos van a los pines de salida
				if botones = "00" then --Reproducir grabado
				pin_boton(0) <= botones(0);
				pin_boton(1) <= botones(1);
				end if;				
				
				if botones = "01" then   --Tocar
				pin_boton(0) <= botones(0);
				pin_boton(1) <= botones(1);
				end if;
				
				if botones = "10" then 	--Grabar
				pin_boton(0) <= botones(0);
				pin_boton(1) <= botones(1);
				end if;    
											
				if botones = "11" then --No hacer na
				pin_boton(0) <= botones(0);
				pin_boton(1) <= botones(1);
				end if;
				
				--Lo que devuelve la raspberry.
				
				if pin_boton_entradas = "00" then
				ANODE <= "1110";  --Se enciende la parte 4 del display
				Display <= "0000000";  --Encender una R en el display
				end if;
				
				if pin_boton_entradas = "01" then
				ANODE <= "1110";   --Se enciende la parte 4 del display
				Display <= "0000010";  --G mal hecha en el display
				end if;
				
				if pin_boton_entradas = "10" then
				ANODE <= "1110";   --Se enciende la parte 4 del display
				Display <= "1001110";  --T mal hecha en el display
				end if;
				
				if pin_boton_entradas = "11" then
				ANODE <= "1110";   --Se enciende la parte 4 del display
				Display <= "0001000";  --Encender todo en el display
				end if;
				
				
				
		when "11" =>  --toda esta  parte ess para mostrar instrumentos
 		
			if switches = "00" then --Piano
			Display<= "0001100"; --enceder una P en el display
		   ANODE<= "0111";  --encender parte 1 del display
			pin_switch(0) <= switches(0);  --enviar el estado de los switches a los pines de salida
			pin_switch(1) <= switches(1);  --enviar el estado de los switches a los pines de salida
			end if;
			
			if switches = "01" then --Ocarina
			Display<= "1000000";   --encender una O en el display
			ANODE<= "0111";    --encender parte 1 del display
			pin_switch(0) <= switches(0);   --enviar el estado de los switches a los pines de salida
			pin_switch(1) <= switches(1);   --enviar el estado de los switches a los pines de salida
			end if;
			
			if switches = "10" then --Ukelele
			Display<= "1000001"; --encender una U en el display
			ANODE<= "0111";   --enceder parte 1 del display
			pin_switch(0) <= switches(0);  --enviar el estado de los switches a los pines de salida
			pin_switch(1) <= switches(1);  --enviar el estado de los switches a los pines de salida
			end if;
			
			if switches = "11" then --Electrónico/Sintetizador
			Display<= "0000110";    --encender una E en el display
			ANODE<= "0111";   --encender parte 1 del display
			pin_switch(0) <= switches(0);  --enviar el estado de los switches a los pines de salida
			pin_switch(1) <= switches(1);  --enviar el estado de los switches a los pines de salida
			end if;
			
			
			--cuando el contador es 01, 10 o da error pues apaga el display
		when others => 	ANODE <= "1111";  --cuando son otros apagar el display
				Display <= "1111111";
	end case;

end process;


end Behavioral;	