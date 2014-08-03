#include "cube.h"
#include "particles/particles.h"

struct ptest
{

	ptest()
    {
		float mass = 1.0f;
		float density = 1.0f;
		// int lifetime1 = 3500;
		// int rate1 = 1;
		int lifetime2 = 15000;
		int rate2 = 50;
		int lifetime3 = 150;
		int rate3 = 10;

		/** Renderer types and instances **/

		particle_renderer_type* pr_type_ball = add_particle_renderer_type("ball_renderer", "packages/particles/ball1.png", "shader", "billboard_renderer");
		pr_type_ball->attributes["r"] = 255.0f;
		pr_type_ball->attributes["g"] = 255.0f;
		pr_type_ball->attributes["b"] = 255.0f;
		pr_type_ball->attributes["a"] = 0.3f;
		pr_type_ball->attributes["size"] = 20.0f;

		particle_renderer_type* pr_type_smoke = add_particle_renderer_type("smoke_renderer", "<grey>packages/particles/smoke.png", "shader", "billboard_renderer");
		pr_type_smoke->attributes["r"] = 255.0f;
		pr_type_smoke->attributes["g"] = 220.0f;
		pr_type_smoke->attributes["b"] = 220.0f;
		pr_type_smoke->attributes["a"] = 0.1f;
		pr_type_smoke->attributes["size"] = 75.0f;

		particle_renderer_instance* pr_inst_fire = pr_type_ball->create_instance("fire");
		pr_inst_fire->attributes["r"] = 200.0f;
		pr_inst_fire->attributes["b"] = 0.0f;

		particle_renderer_instance* pr_inst_poison = pr_type_ball->create_instance("poison");
		pr_inst_fire->attributes["r"] = 0.0f;
		pr_inst_fire->attributes["b"] = 200.0f;

		particle_renderer_instance* pr_inst_smoke = pr_type_smoke->create_instance("smoke");

		/** Particle types **/

		particle_type* p_type_fire = add_particle_type("fire", "fire");
		particle_type* p_type_poison = add_particle_type("poison", "poison");
		particle_type* p_type_smoke = add_particle_type("smoke", "smoke");

		/** Modifier types and instances **/

		particle_modifier_type* pm_type_velocity_transformation = add_particle_modifier_type("velocity_transformation", "velocity_transformation");
		particle_modifier_instance* pm_inst_velocity_transformation = pm_type_velocity_transformation->create_instance();

		particle_modifier_type* pm_type_mass_spring_transformation = add_particle_modifier_type("mass_spring_transformation", "mass_spring_transformation");
		particle_modifier_instance* pm_inst_mass_spring_transformation = pm_type_mass_spring_transformation->create_instance();

		particle_modifier_type* pm_type_randomv = add_particle_modifier_type("randomv", "randomv");
		particle_modifier_instance* pm_inst_randomv = pm_type_randomv->create_instance();

		particle_modifier_type* pm_type_randomw = add_particle_modifier_type("randomw", "randomw");
		particle_modifier_instance* pm_inst_randomw = pm_type_randomw->create_instance();

		particle_modifier_type* pm_type_gravity_point = add_particle_modifier_type("gravity_point", "gravity_point");
		pm_type_gravity_point->attributes["mass"] = 1000.0f;
		pm_type_gravity_point->attributes["gravity"] = 0.8f;
		particle_modifier_instance* pm_inst_gravity_point_1 = pm_type_gravity_point->create_instance(vec(768.0f, 768.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_2 = pm_type_gravity_point->create_instance(vec(256.0f, 256.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_3 = pm_type_gravity_point->create_instance(vec(768.0f, 256.0f, 532.0f));
		particle_modifier_instance* pm_inst_gravity_point_4 = pm_type_gravity_point->create_instance(vec(256.0f, 768.0f, 532.0f));

		particle_modifier_instance* pm_inst_gravity_point_5 = pm_type_gravity_point->create_instance(vec(768.0f, 768.0f, 532.0f));
		pm_inst_gravity_point_5->attributes["mass"] = 5000.0f;
		pm_type_gravity_point->attributes["gravity"] = 1.8f;

		/** Emitter types and instances **/

		particle_emitter_type* pe_point_fire_type = add_particle_emitter_type("special_point_emitter", "fire", mass, density, lifetime2, rate2, "point_emitter");
		particle_emitter_instance* pe_inst_point_1 = pe_point_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(-40.0f, 0.0f, 0.0f));
		particle_emitter_instance* pe_inst_point_2 = pe_point_fire_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, -40.0f, 0.0f));

		particle_emitter_type* pe_point_poison_type = add_particle_emitter_type("special_point_emitter", "poison", mass, density, lifetime2, rate2, "point_emitter");
		particle_emitter_instance* pe_inst_point_3 = pe_point_poison_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(40.0f, 0.0f, 0.0f));
		particle_emitter_instance* pe_inst_point_4 = pe_point_poison_type->create_instance(vec(512.0f, 512.0f, 514.0f), vec(0.0f, 40.0f, 0.0f));

		particle_emitter_type* pe_field_type = add_particle_emitter_type("special_field_emitter", "smoke", mass, density, lifetime3, rate3, "field_emitter");
		pe_field_type->attributes["grid_size_x"] = 3.0f;
		pe_field_type->attributes["grid_size_y"] = 3.0f;
		pe_field_type->attributes["grid_size_z"] = 3.0f;
		pe_field_type->attributes["grid_dist"] = 20.0f;
		particle_emitter_instance* pe_inst_field_1 = pe_field_type->create_instance(vec(768.0f, 768.0f, 514.0f), vec(0.0f, 0.0f, 0.0f));

		/** Connect emitters and modifiers **/

		pe_inst_point_1->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_2->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_3->add_modifier(pm_inst_velocity_transformation);
		pe_inst_point_4->add_modifier(pm_inst_velocity_transformation);
		pe_inst_field_1->add_modifier(pm_inst_velocity_transformation);

		pe_inst_point_1->add_modifier(pm_inst_randomv);
		pe_inst_point_2->add_modifier(pm_inst_randomv);
		pe_inst_point_3->add_modifier(pm_inst_randomv);
		pe_inst_point_4->add_modifier(pm_inst_randomv);
		pe_inst_field_1->add_modifier(pm_inst_randomw);

		pe_inst_point_1->add_modifier(pm_inst_gravity_point_1);
		pe_inst_point_2->add_modifier(pm_inst_gravity_point_2);
		pe_inst_point_3->add_modifier(pm_inst_gravity_point_3);
		pe_inst_point_4->add_modifier(pm_inst_gravity_point_4);

		pe_inst_field_1->add_modifier(pm_inst_gravity_point_5);
    }

};

ptest *ptest_inst = new ptest();