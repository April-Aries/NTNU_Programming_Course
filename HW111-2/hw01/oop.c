#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include"oop.h"

/* print potato function */

void print_potato(const struct Potato *this)
{
    printf("Potato:\n");
    printf("  weight: %d\n", this->weight );
    printf("  produced by: %s\n", this->producer_name );

    return;
}

void print_magical_potato(const struct Potato *this)
{
    printf("Magical Potato:\n");
    printf("  weight: %d\n", this->weight );
    printf("  produced by: %s\n", this->producer_name );
    printf("  magical effect: %s\n", MagicalEffectToString[ ( *( enum MagicalEffect *)( this + 1 ) ) - 1 ] );
    printf("  magic level: %d\n", *( int32_t *)( ( enum MagicalEffect *)( this + 1 ) + 1 ));

    return;
}

/* potato dtor functions */

void potato_dtor(struct Potato **obj)
{
    free( *obj );

    return;
}

void magical_potato_dtor(struct Potato **obj)
{
    free( ( struct MagicalPotato* )*obj );

    return;
}

/* print potato balls functions */

void print_potato_ball(const struct PotatoBall *this)
{
    printf("Potato Ball:\n");
    printf("  weight: %d\n", this->weight );
    printf("  produced by: %s\n", this->producer_name);

    return;
}

void print_magical_potato_ball(const struct PotatoBall *this)
{
    printf("Magical Potato ball:\n");
    printf("  weight: %d\n", this->weight );
    printf("  produced by: %s\n", this->producer_name );
    printf("  magical effect: %s\n", MagicalEffectToString[ ( *( enum MagicalEffect* )( this + 1 ) ) - 1 ] );
    printf("  magic level: %d\n", *( int32_t *)( ( enum MagicalEffect* )( this + 1 ) + 1 ) );

    return;
}

/* potato balls dtor functions */

void potato_ball_dtor(struct PotatoBall **obj)
{
    free( *obj );

    return;
}

void magical_potato_ball_dtor(struct PotatoBall **obj)
{
    free( ( struct MagicPotatoBall* )*obj );

    return;
}

/* fry functions */

struct PotatoBall *fry_potato_ball(struct Potato **input)
{
    /* potato ball */
    struct PotatoBall *ball = calloc( 1, sizeof( struct PotatoBall ) );

    ball->producer_name = (*input)->producer_name;

    ball->weight = (*input)->weight;

    ball->print = print_potato_ball;
    ball->dtor = potato_ball_dtor;

    /* potato */
    potato_dtor( input );

    return ball;
}

struct PotatoBall *fry_magical_potato_ball(struct Potato **input)
{
    /* magical potato ball */
    struct MagicalPotatoBall *ball = calloc( 1, sizeof( struct PotatoBall ) );

    ball->base.producer_name = (*input)->producer_name;

    ball->base.weight = (*input)->weight;

    ball->base.print = print_magical_potato_ball;
    ball->base.dtor = magical_potato_ball_dtor;

    ball->effect = *(enum MagicalEffect *)( (*input) + 1 ) ;
    ball->effect_level = *( int32_t *)( ( enum MagicalEffect * )( (*input) + 1 ) + 1 );

    /* potato */
    magical_potato_dtor( input );

    return ( struct PotatoBall *)ball;
}

/* produce functions */

struct Potato *smallten_summon_potato(const struct PotatoProducer *this)
{
    srand( time( NULL ) );
    struct MagicalPotato *p = calloc( 1, sizeof( struct MagicalPotato ) );
    p->base.weight = abs( rand() ) % 1000 + 1;
    p->base.producer_name = this->name;
    p->base.print = print_magical_potato;
    p->base.fry = fry_magical_potato_ball;

    p->effect = rand() % 4 + 1;
    p->effect_level = rand() % 10 + 1;

    return ( struct Potato * )p;
}

struct Potato *subarya_produce_potato(const struct PotatoProducer *this)
{
    srand( time( NULL ) );
    struct Potato *p = calloc( 1, sizeof( struct Potato ) );
    p->weight = abs( ( ( 55 * rand() ) + ( rand() * rand() ) ) % 1000 + 1 );
    p->producer_name = this->name;
    p->print = print_potato;
    p->fry = fry_potato_ball;

    return p;
}

/* Init Producer */

void init_smallten(struct PotatoProducer *obj)
{
    strncpy( obj->name, "smallten", 8 );
    obj->name[8] = 0;

    obj->produce = smallten_summon_potato;

    return;
}

void init_subarya(struct PotatoProducer *obj)
{
    strncpy( obj->name, "subarya", 7 );
    obj->name[7] = 0;

    obj->produce = subarya_produce_potato;

    return;
}
