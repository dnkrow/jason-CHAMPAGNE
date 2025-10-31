#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

#define STATE_FILE "/tmp/countdown_state.txt"
#define SOUND_CMD "paplay /usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga 2>/dev/null || aplay /usr/share/sounds/alsa/Front_Center.wav 2>/dev/null || printf '\\a'"

typedef struct {
    time_t start_time;
    int duration_seconds;
    int is_running;
} TimerState;

// Sauvegarder l'état du timer
void save_state(TimerState *state) {
    FILE *f = fopen(STATE_FILE, "w");
    if (f) {
        fprintf(f, "%ld\n%d\n%d\n", state->start_time, state->duration_seconds, state->is_running);
        fclose(f);
    }
}

// Charger l'état du timer
int load_state(TimerState *state) {
    FILE *f = fopen(STATE_FILE, "r");
    if (f) {
        if (fscanf(f, "%ld\n%d\n%d\n", &state->start_time, &state->duration_seconds, &state->is_running) == 3) {
            fclose(f);
            return 1;
        }
        fclose(f);
    }
    return 0;
}

// Calculer le temps restant
int get_remaining_time(TimerState *state) {
    time_t current_time = time(NULL);
    int elapsed = (int)difftime(current_time, state->start_time);
    int remaining = state->duration_seconds - elapsed;
    return remaining > 0 ? remaining : 0;
}

// Envoyer une notification système
void send_notification(const char *title, const char *message) {
    char cmd[512];
    // Utilise notify-send sur Linux
    snprintf(cmd, sizeof(cmd), "notify-send -u critical -t 0 '%s' '%s' 2>/dev/null", title, message);
    system(cmd);
}

// Jouer un son d'alarme
void play_sound() {
    system(SOUND_CMD);
}

// Afficher le temps formaté
void display_time(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;
    
    printf("\r⏱️  Temps restant: %02d:%02d:%02d", hours, minutes, secs);
    fflush(stdout);
}

// Handler pour SIGINT (Ctrl+C)
void sigint_handler(int sig) {
    printf("\n\n✅ Timer sauvegardé. Vous pouvez relancer le programme pour reprendre.\n");
    exit(0);
}

// Créer une notification persistante (bonus)
void create_persistent_notification(int remaining) {
    char cmd[512];
    int hours = remaining / 3600;
    int minutes = (remaining % 3600) / 60;
    int secs = remaining % 60;
    
    // Notification persistante avec dunst ou notify-send
    snprintf(cmd, sizeof(cmd), 
             "notify-send -u normal -t 0 -h string:x-canonical-private-synchronous:countdown "
             "'⏱️ Compte à rebours' 'Temps restant: %02d:%02d:%02d' 2>/dev/null",
             hours, minutes, secs);
    system(cmd);
}

// Fonction principale du timer
void run_timer(int duration_seconds) {
    TimerState state;
    
    // Vérifier s'il existe un timer en cours
    if (load_state(&state) && state.is_running) {
        printf("🔄 Timer existant détecté!\n");
        int remaining = get_remaining_time(&state);
        
        if (remaining > 0) {
            printf("⏰ Reprise du timer avec %d secondes restantes\n\n", remaining);
        } else {
            printf("⏰ Le timer précédent est terminé!\n");
            state.is_running = 0;
            save_state(&state);
        }
    } else {
        // Nouveau timer
        state.start_time = time(NULL);
        state.duration_seconds = duration_seconds;
        state.is_running = 1;
        save_state(&state);
        printf("▶️  Démarrage du timer: %d secondes\n\n", duration_seconds);
    }
    
    // Installer le handler de signal
    signal(SIGINT, sigint_handler);
    
    // Boucle principale
    while (state.is_running) {
        int remaining = get_remaining_time(&state);
        
        if (remaining > 0) {
            display_time(remaining);
            
            // Notification persistante toutes les 5 secondes (bonus)
            if (remaining % 5 == 0) {
                create_persistent_notification(remaining);
            }
            
            sleep(1);
        } else {
            // Timer terminé!
            printf("\n\n🔔 TIMER TERMINÉ!\n");
            
            // Jouer le son
            play_sound();
            
            // Envoyer la notification
            send_notification("⏰ Timer terminé!", "Le compte à rebours est arrivé à 0!");
            
            // Afficher le message de redirection
            printf("\n📍 Redirection vers le composant...\n");
            printf("   (Dans une vraie app, on appellerait la fonction de navigation ici)\n\n");
            
            // Marquer comme terminé
            state.is_running = 0;
            save_state(&state);
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int duration;
    
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   COMPTE À REBOURS EN C              ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
    
    if (argc > 1) {
        duration = atoi(argv[1]);
        if (duration <= 0) {
            printf("❌ Erreur: La durée doit être un nombre positif\n");
            return 1;
        }
    } else {
        printf("Entrez la durée en secondes: ");
        if (scanf("%d", &duration) != 1 || duration <= 0) {
            printf("❌ Erreur: Durée invalide\n");
            return 1;
        }
    }
    
    run_timer(duration);
    
    printf("✅ Programme terminé.\n");
    return 0;
}
