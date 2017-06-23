/*
#############################################################################################
#    Tux in Space - space exploration game													#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
#																							#
#    This program is free software; you can redistribute it and/or modify					#
#    it under the terms of the GNU General Public License as published by					#
#    the Free Software Foundation, version 3 or compatibles.								#
#																							#
#    This program is distributed in the hope that it will be useful,						#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of							#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the							#
#    GNU General Public License for more details.											#
#																							#
#    You should have received a copy of the GNU General Public License						#
#    along with this program; if not, write to the Free Software							#
#    Foundation, Inc.																		#
#############################################################################################
 *
 * Low level math functions
 *
 */

#include <cstdlib>
#include <cmath>
#include <ctime>
#include "math.h"

/***
 * Return a "random" int in a range given, but the gap can't be greater than 100
 */
int math_RandomI (int min, int max) {
	srand(time(nullptr));
	return (rand() % (max - min)) + min;
}


// TFORCE SCALAR

long double tforce_scalar::value() const {
	return m;
}

// TPOSITION

tposition tposition::operator- (const tposition& p) const {
	return tposition(v - p.v);
}
void tposition::operator+= (const tposition& p) {
	v += p.v;
}
tpositionmass tposition::operator* (const tmass& m) const{
	return tpositionmass(v * m.m);
}
tlength tposition::scalar() const {
	return v.length();
}
vec3<long double> tposition::direction() const{
	return v.direction();
}

// TPOSITIONMASS

tposition tpositionmass::operator/ (const tmass& m){
	return tposition(v / m.m);
}

// TAREA

tvolume tarea::operator* (const tlength& l){
	return tvolume(m * l.m);
}

// TLENGTH

tarea tlength::operator* (const tlength& l){
	return tarea(m * l.m);
}

// TGUC

tforce tguc::newton(const tmass& mass1, const tmass& mass2, const tposition& dist) {
	// apply the newton law of gravitation
	tforce f(
		dist.direction(),
		m * mass1.value() * mass2.value() / (dist.scalar().value() * dist.scalar().value())
	);
	return f;
}

// TVELOCITY

tmomentum tvelocity::operator* (const tmass& m) const{
	return tmomentum(v * m.m);
}
vec3<long double> tvelocity::value() const{
	return v;
}
void tvelocity::operator+= (const tvelocity& t){
	v += t.v;
}
tposition tvelocity::operator* (const time_raw& t) const {
	return tposition(v * t.time());
}
tspeed tvelocity::scalar() const{
	return tspeed(v.length());
}
tmomentum tvelocity::operator* (const tmass& m) const;
tvelocity tvelocity::operator+ (const tvelocity& vel) const{
	return tvelocity(v+vel.v);
}
tvelocity tvelocity::operator- (const tvelocity& vel) const{
	return tvelocity(v-vel.v);
}
bool tvelocity::operator< (const tvelocity& vel) const {
	return v.length() < vel.v.length();
}
bool tvelocity::operator> (const tvelocity& vel) const {
	return v.length() > vel.v.length();
}
tacceleration tvelocity::operator/ (const time_raw& t) const{
	return tacceleration(v / t.time());
}

// TSPEED

long double tspeed::value() const {
	return m;
}
tspeed tspeed::operator+ (const tspeed& s) const{
	return tspeed(m + s.m);
}
tspeed tspeed::operator- (const tspeed& s) const{
	return tspeed(m - s.m);
}
tacceleration_scalar tspeed::operator/ (const time_raw& t) const {
	return tacceleration_scalar(m/t.time());
}

// TACCELERATION

tforce tacceleration::operator* (const tmass& m) const{
		return tforce(v * m.m);
};
long double tacceleration::value() const {
	return v.length();
}

// TACCELERATION_SCALAR

tacceleration_scalar tacceleration_scalar::operator/ (const long double& n) const{
			return tacceleration_scalar(m/n);
}
tacceleration_scalar tacceleration_scalar::operator* (const long double& n) const{
	return tacceleration_scalar(m*n);
}
	
inline long double tacceleration_scalar::value() const {
	return m;
}

// TMOMENTUM

tvelocity tmomentum::operator/ (const tmass& m){
	return tvelocity(v / m.value());
}
tmomentum tmomentum::operator+ (const tmomentum& i){
	return tmomentum(v + i.v);
}
vec3<long double> tmomentum::value() const {
	return v;
}

// TMOMENTUM SCALAR

tmomentum_scalar tmomentum_scalar::operator+ (const tmomentum_scalar& s) const{
	return tmomentum_scalar(m + s.m);
};
tenergy tmomentum_scalar::operator* (const tspeed& s) const{
	return tenergy(m * s.value());	
}
tmomentum_scalar tmomentum_scalar::operator/ (const long double& n) const{
	return tmomentum_scalar(m/n);
}
tmomentum_scalar tmomentum_scalar::operator* (const long double& n) const{
	return tmomentum_scalar(m/n);
}
tforce_scalar tmomentum_scalar::operator/ (const time_raw& t) const{
	return tforce_scalar(m/t.time());
}

// TMASS

tmomentum tmass::operator* (const tvelocity& vel) const{
	return tmomentum(vel.value() * m);
}
tmass tmass::operator/ (const long double& n) const{
	return tmass(m/n);
}
void tmass::operator= (const tmass& t) {
	m = t.m;
}
void tmass::operator>> (std::ostream& s){
	s << std::to_string(m);
}
void tmass::operator+= (const tmass& t) {
	m += t.m;
}
void tmass::operator*= (const long double& pure) {
	m *= pure;
}
tmass tmass::operator* (const long double& pure) const{
	return tmass(m * pure);
}
tforce_scalar tmass::operator* (const tacceleration_scalar& a) const{
	return tforce_scalar(m * a.value());
}
tmomentum_scalar tmass::operator* (const tspeed& v) const{
	return tmomentum_scalar(v.value() * m);
}
long double tmass::operator/ (const tmass& t) const{
	return m / t.m;
}
tmass tmass::operator+ (const tmass& t) const {
	return tmass(m + t.m);
}
bool tmass::operator> (const tmass& t) const {
	if(m > t.m)
		return true;
	return false;
}
bool tmass::operator< (const tmass& t) const {
	if(m < t.m)
		return true;
	return false;
}
long double tmass::value() const {
	return m;
}


// TENERGY
tenergy tenergy::operator+ (const tenergy& e) const{
	return tenergy(m + e.m);
}
tenergy tenergy::operator- (const tenergy& e) const{
	return tenergy(m - e.m);
}
long double tenergy::value() const{
	return m;
}























