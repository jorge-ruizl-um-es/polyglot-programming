# Vamos a incluir tres tipos de items: uno para acelerar las balas durante una cantidad de tiempo,
# otro para aumentar el tamaño de las balas durante una cantidad de tiempo, y un último para duplicar 
# temporalmente la cantidad de puntos recibidos.

# type 1 = orange
# type 2 = yellow
# type 3 = green

# type 4 = blue
# type 5 = red      --> EXTRA LIFE

# Idea: añadir item maligno para duplicar la cantidad de enemigos

import pygame
import random

numeros = list(range(1, 6))
probabilities = [0.2, 0.15, 0.25, 0.33, 0.07]


class Items:
    def __init__(self, x, y, vel):
        # el personaje tiene unas coordenadas donde se encuentra, unas dimensiones, velocidad, color
        # y un atributo Rect para que el módulo pygame pueda construirlo en pantalla como un objeto.
        self._x = x
        self._y = y
        self._ancho = 60
        self._alto = 60
        self._velocidad = vel
        self._type = random.choices(numeros, weights=probabilities, k=1)[0]
        self._color = self._select_color()
        self._rect = pygame.Rect(self._x, self._y, self._ancho, self._alto) # cambia las coordenadas
        self._imagen = pygame.image.load(self._select_image()) # cargar imagen del enemigo
        self._imagen = pygame.transform.scale(self._imagen, (self._ancho, self._alto))
    
    def _select_color(self):
        match self._type:
            case 1:
                return "orange"
            case 2:
                return "yellow"
            case 3:
                return "green"
            case 4:
                return "blue"
            case 5:
                return "red"
    
    def _select_image(self):
        cadena = "media/"
        match self._type:
            case 1:
                cadena += "size.png"
            case 2:
                cadena += "speed.png"
            case 3:
                cadena += "coin.webp"
            case 4:
                cadena += "bad_item.png"
            case 5:
                cadena += "heart.png"
        return cadena

    def set_x(self, new_x):
        self._x = new_x
    
    def set_y(self, new_y):
        self._y = new_y

    def get_y(self):
        return self._y

    def get_size(self):
        return [self._ancho, self._alto]

    def get_speed(self):
        return self._velocidad
    
    def mult_speed(self):
        self._velocidad *= 1.25
    
    def get_color(self):
        return self._color
    
    def get_rect(self):
        return self._rect

    def get_type(self):
        return self._type
    
    def dibujar(self, ventana):
        self._rect = pygame.Rect(self._x, self._y, self._ancho, self._alto) # hay que llamarla para que las coordenadas cambien
        # pygame.draw.rect(ventana, self._color, self._rect)  # comando para representar el cubo en pantalla
        ventana.blit(self._imagen, (self._x, self._y))      # comando para representar la imagen

    def movimiento(self):
        # mueve instancias de Enemigo hacia abajo
        self._y += self._velocidad