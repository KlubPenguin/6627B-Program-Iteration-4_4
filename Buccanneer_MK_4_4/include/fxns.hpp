#pragma once

#include "ios.hpp"

void hangFXN();
void hangInitialize();
void hangDisabled();
void hangDown();
void hangUp();

void intakeFXN();
void intakeIn();
void intakeStop();
void intakeOut();

void driveFXN();
void lemlibDrive();
void odomDisplay();
void loopOdomDisplay();

void catapultStart();
void catapultFXN();
void catapultDisplay();

void wingsFXN();
void delayOpen(int delay, pros::ADIDigitalOut& wing); 
void open(pros::ADIDigitalOut& wing);
void delayClose(int delay, pros::ADIDigitalOut& wing);
void close(pros::ADIDigitalOut& wing);
void frontWingsOpen();
void frontWingsClose();
void backWingsOpen();
void backWingsClose();
void delayOpen(std::string face, int delay);
void delayClose(std::string face, int delay);

void displayFXN();