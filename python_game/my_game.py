import pygame
import random
from personaje import Cubo
from enemigo import Enemigo
from bala import Bala
from items import Items

pygame.init()   # iniciar juego
pygame.mixer.init()    # iniciar procesador de sonidos

# CONSTANTES

# constantes para la pantalla que se abre al iniciar el juego
ANCHO = 1000
ALTO = 800
FPS = 60
VENTANA = pygame.display.set_mode([ANCHO, ALTO])
FUENTE = pygame.font.SysFont("Courier New", 40)
FUENTE2 = pygame.font.SysFont("Comic Sans", 20)
SONIDO_DISPARO = pygame.mixer.Sound("media/bullet.mp3")
SONIDO_MUERTE = pygame.mixer.Sound("media/die.mp3")
# SOUNDTRACK = pygame.mixer.Sound("media/arcade.mp3")   # musica de fondo
SONIDO_COIN = pygame.mixer.Sound("media/coin.mp3")
SONIDO_VIDA = pygame.mixer.Sound("media/extra_life.mp3")
SONIDO_MALO = pygame.mixer.Sound("media/bad.mp3")
SONIDO_ITEM = pygame.mixer.Sound("media/level_up.mp3")

# sistema de vidas y puntos
vida = 5
puntos = 0

# control del tiempo
jugando = True
reloj = pygame.time.Clock()
tiempo_total = 0
tiempo_pasado_en = 0
tiempo_pasado_it = 0
tiempo_entre_balas = default_tiempo_entre_balas = 500 
contador_tiempo_balas = 100
tiempo_entre_enemigos = default_tiempo_entre_enemigos = 400     # 400 milisegundos entre que aparecen dos enemigos
tiempo_entre_items = 5000

# control de items
bala_grande = False
tiempo_bala_grande = 0
limite_tamano_bala = 40
bala_rapida = False
tiempo_bala_rapida = 0
puntos_dobles = False
tiempo_puntos_dobles = 0
double_enemies = False
tiempo_enemigos_dobles = 0

# personajes del juego
cubo = Cubo(ANCHO/2, ALTO-75)   # personaje, instancia de la clase Cubo, colocado en la posición 100x100
velocidad_enemigos = default_vel_enemy = 6
velocidad_balas = default_vel_bala = 10
lado_bala = default_size_bala = 10
enemigos = []   # lista que contiene a todos los enemigos que aparecerán
balas = []
items = []

enemigos.append(Enemigo(ANCHO/2, 100, velocidad_enemigos))  # añadir elemento inicial

# FUNCIONES

# función para crear una bala para disparar a los enemigos
def crear_bala():
    balas.append(Bala(cubo.get_rect().centerx, cubo.get_rect().centery, velocidad_balas, lado_bala))
    SONIDO_DISPARO.play()

# función para controlar qué va a hacer el personaje o el juego ante cada pulsación
# MOVIMIENTO con WASD
def gestionar_teclas(teclas):   
    posiciones = cubo.get_position()   # lista de dos elementos, x e y
    global contador_tiempo_balas 
    """"
    if teclas[pygame.K_w]:      # pygame.K_(tecla) representa la tecla que sea
        cubo.set_y(posiciones[1] - cubo.get_speed()) # si se resta, va hacia arriba, si se suma, hacia abajo
    if teclas[pygame.K_s]:      # no ponemos elif para que se puedan pulsar varias a la vez
        cubo.set_y(posiciones[1] + cubo.get_speed())
    """
    if teclas[pygame.K_a]:        # aceptar solo desplazamiento lateral
        if cubo.get_position()[0] >= 0:
            cubo.set_x(posiciones[0] - cubo.get_speed())
    if teclas[pygame.K_d]:
        if cubo.get_position()[0] + cubo.get_size()[0] <= ANCHO: 
            cubo.set_x(posiciones[0] + cubo.get_speed())
    if teclas[pygame.K_SPACE] and contador_tiempo_balas > tiempo_entre_balas:
        crear_bala()
        contador_tiempo_balas = 0


# PROGRAMA PRINCIPAL - el juego es un bucle

while jugando and vida>0:
    tiempo = reloj.tick(FPS)
    tiempo_pasado_en += tiempo    # añadimos los milisegundos que van pasando en la ejecución
    tiempo_pasado_it += tiempo
    tiempo_total += tiempo
    contador_tiempo_balas += tiempo

    if tiempo_pasado_en > tiempo_entre_enemigos:
        enemigos.append(Enemigo(random.randint(0, ANCHO), -100, velocidad_enemigos))    # añadir un enemigo en una posición aleatoria del eje x
        tiempo_pasado_en = 0
    
    if tiempo_total % 1000 == 0 and velocidad_enemigos < 25:
        velocidad_enemigos*=1.15
        default_vel_enemy = velocidad_enemigos
    
    if tiempo_pasado_it > tiempo_entre_items and random.random() > 0.8:     # crear un item con una probabilidad del 20% cada 5 sega
        items.append(Items(random.randint(0, ANCHO), -100, random.randint(8, 14)))
        tiempo_pasado_it = 0
    
    if velocidad_enemigos > 15 and velocidad_enemigos < 25:
        tiempo_entre_enemigos = 150
        tiempo_entre_balas = 400
        tiempo_entre_items = 4200
        velocidad_balas = 17
    
    if velocidad_enemigos >= 25:
        tiempo_entre_enemigos = 100
        default_tiempo_entre_enemigos = tiempo_entre_enemigos
        tiempo_entre_items = 3800
        tiempo_entre_balas = 300
        velocidad_balas = 20

    eventos = pygame.event.get()    # devuelve lista de eventos, todas las posibles acciones que pueden hacerse en el juego

    teclas = pygame.key.get_pressed()   # devuelve lista de teclas que se presionan en cada momento

    texto_vida = FUENTE.render(f"Vida: {vida}", True, "white")
    texto_puntos = FUENTE.render(f"Puntos: {puntos}", True, "white")
    texto_size = FUENTE2.render("¡SIZE X2!", True, "white")
    texto_vel = FUENTE2.render("¡VEL X2!", True, "white")
    puntos_dob_text = FUENTE2.render("¡POINT X2!", True, "white")

    gestionar_teclas(teclas)

    for evento in eventos:
        if evento.type == pygame.QUIT:  # si detecta en algún momento un evento del tipo QUIT, cerrar el juego
            jugando = False

    VENTANA.fill("black")   # rellenar la pantalla en negro antes de representar el cubo
    # permite que, cuando cambien las coordenadas del cubo, se borre el cubo de la localización anterior
    cubo.dibujar(VENTANA)    # dibujar el cubo en el bucle (puede hacerse antes o después de comprobar eventos)
    
    for enemigo in enemigos:
        # dibujamos cada enemigo que vaya a haber, y lo movemos hacia abajo
        enemigo.dibujar(VENTANA)
        enemigo.movimiento()

        if pygame.Rect.colliderect(cubo.get_rect(), enemigo.get_rect()):
            # control de colisiones entre dos objetos pasando sus rectángulos
            vida-=1
            SONIDO_MUERTE.play()
            if enemigo in enemigos:
                enemigos.remove(enemigo)

        if enemigo.get_y() > ALTO:
            if enemigo in enemigos:
                enemigos.remove(enemigo)
    
    for bala in balas:
        bala.dibujar(VENTANA)
        bala.movimiento()

        for enemigo in enemigos:
            if pygame.Rect.colliderect(bala.get_rect(), enemigo.get_rect()):
                puntos += (2 if puntos_dobles else 1)
                if enemigo in enemigos:
                    enemigos.remove(enemigo)
                if bala in balas:
                    balas.remove(bala)
        
        if bala.get_y() > ALTO:
            balas.remove(bala)
    
    for item in items:
        item.dibujar(VENTANA)
        item.movimiento()

        if pygame.Rect.colliderect(cubo.get_rect(), item.get_rect()):
            match item.get_type():
                case 1:     # tipo 1 (naranja) aumenta el tamaño de las balas durante 7 segundos
                    if lado_bala <= limite_tamano_bala:
                        lado_bala*=2
                        bala_grande = True
                        tiempo_bala_grande = tiempo_total
                        SONIDO_ITEM.play()

                case 2:     # tipo 2 (amarillo) duplica velocidad balas
                    if tiempo_entre_balas > 25:
                        velocidad_balas*=2
                        tiempo_entre_balas/=2
                        bala_rapida = True
                        tiempo_bala_rapida = tiempo_total
                        SONIDO_ITEM.play()

                case 3:     # tipo 3 (verde) duplica puntos
                    puntos_dobles = True
                    tiempo_puntos_dobles = tiempo_total
                    SONIDO_COIN.play()

                case 4:     # tipo 4 (rojo) duplica enemigos
                    double_enemies = True
                    tiempo_entre_enemigos/=2
                    velocidad_enemigos*=1.2
                    tiempo_enemigos_dobles = tiempo_total
                    SONIDO_MALO.play()
                    # añadir texto pantalla grande

                case 5:     # tipo 5 (azul) vida extra
                    vida+=1
                    SONIDO_VIDA.play()
                    # añadir texto pantalla grande

            items.remove(item)
        
        if item.get_y() > ALTO:
            items.remove(item)
    
    # control de fin de efectos secundarios producidos por items
    # aquellos que se prolonguen en el tiempo duran 7 segundos
    if bala_grande and tiempo_total - tiempo_bala_grande >= 7000:
        lado_bala = default_size_bala
        bala_grande = False

    if bala_rapida and tiempo_total - tiempo_bala_rapida >= 7000:
        velocidad_balas = default_vel_bala
        tiempo_entre_balas = default_tiempo_entre_balas
        bala_rapida = False
    
    if puntos_dobles and tiempo_total - tiempo_puntos_dobles >= 7000:
        puntos_dobles = False
    
    if double_enemies and tiempo_total - tiempo_enemigos_dobles >= 7000:
        double_enemies = False
        tiempo_entre_enemigos = default_tiempo_entre_enemigos
        velocidad_enemigos = default_vel_enemy

    # mostrar texto por pantalla
    VENTANA.blit(texto_vida, (20, 20))
    VENTANA.blit(texto_puntos, (20, 60))
    if bala_grande:
        VENTANA.blit(texto_size, (20, 110))
    if bala_rapida:
        VENTANA.blit(texto_vel, (140, 110))
    if puntos_dobles:
        VENTANA.blit(puntos_dob_text, (260, 110))

    pygame.display.update()

pygame.quit()

nombre = input("Introduce tu nombre: ")

with open("scores.txt", "a") as archivo:
    if len(nombre) < 15:
        archivo.write(f"{nombre} - {puntos}\n")

# quit()