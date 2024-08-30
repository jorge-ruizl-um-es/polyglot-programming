import pygame

class Cubo:
    def __init__(self, x, y):
        # el personaje tiene unas coordenadas donde se encuentra, unas dimensiones, velocidad, color
        # y un atributo Rect para que el módulo pygame pueda construirlo en pantalla como un objeto.
        self._x = x
        self._y = y
        self._ancho = 50
        self._alto = 50
        self._velocidad = 10
        self._color = "pink"
        self._rect = pygame.Rect(self._x, self._y, self._ancho, self._alto) # cambia las coordenadas
        self._imagen = pygame.image.load("media/nave.webp") # cargar imagen del personaje
        self._imagen = pygame.transform.scale(self._imagen, (self._ancho, self._alto))
        # self._imagen = pygame.transform.rotate(self._imagen, 90)  # si hubiera que rotarla

    def set_x(self, new_x):
        self._x = new_x
    
    def set_y(self, new_y):
        self._y = new_y

    def get_position(self):
        return [self._x, self._y]

    def get_size(self):
        return [self._ancho, self._alto]

    def get_speed(self):
        return self._velocidad
    
    def get_color(self):
        return self._color
    
    def get_rect(self):
        return self._rect
    
    def dibujar(self, ventana):
        self._rect = pygame.Rect(self._x, self._y, self._ancho, self._alto) # hay que llamarla para que las coordenadas cambien
        # pygame.draw.rect(ventana, self._color, self._rect)  # comando para representar el cubo en pantalla
        ventana.blit(self._imagen, (self._x, self._y))