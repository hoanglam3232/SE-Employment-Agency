-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema employment_agency_final
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema employment_agency_final
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `employment_agency_final` ;
-- -----------------------------------------------------
-- Schema employment_agency
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema employment_agency
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `employment_agency` ;
USE `employment_agency_final` ;

-- -----------------------------------------------------
-- Table `employment_agency_final`.`login_account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`login_account` (
  `id` INT NULL DEFAULT NULL,
  `email` VARCHAR(100) NOT NULL,
  `password` VARCHAR(100) NOT NULL,
  `user_type` VARCHAR(20) NOT NULL,
  `gender` VARCHAR(10) NULL DEFAULT NULL,
  `date_of_birth` DATE NULL DEFAULT NULL,
  `phone_number` CHAR(12) NULL DEFAULT NULL,
  `account_image` BLOB NULL DEFAULT NULL,
  `registration_date` DATE NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX (`id` ASC) VISIBLE,
  UNIQUE INDEX (`email` ASC) VISIBLE);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`seeker`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`seeker` (
  `seeker_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `CV` LONGBLOB NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  UNIQUE INDEX (`seeker_id` ASC) VISIBLE,
  PRIMARY KEY (`seeker_id`),
  CONSTRAINT `FK_loginAccount_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency_final`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`education_info`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`education_info` (
  `seeker_id` INT NOT NULL,
  `degree_name` VARCHAR(50) NOT NULL,
  `major` VARCHAR(50) NOT NULL,
  `school_name` VARCHAR(50) NOT NULL,
  `gpa` FLOAT NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`seeker_id`, `degree_name`, `major`, `school_name`),
  CONSTRAINT `fk_education_info_seeker_prof1`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency_final`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`experience_info`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`experience_info` (
  `seeker_id` INT NOT NULL,
  `company_name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `work_address` VARCHAR(150) NULL DEFAULT NULL,
  `start_date` DATE NULL DEFAULT NULL,
  `end_date` DATE NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`seeker_id`, `company_name`, `job_title`),
  CONSTRAINT `fk_experience_info_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency_final`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`recruiter`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`recruiter` (
  `recruiter_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `from_company` VARCHAR(100) NOT NULL,
  `company_description` VARCHAR(500) NOT NULL,
  `company_image` BLOB NULL DEFAULT NULL,
  `company_url` VARCHAR(60) NULL DEFAULT NULL,
  UNIQUE INDEX (`recruiter_id` ASC) VISIBLE,
  PRIMARY KEY (`recruiter_id`),
  CONSTRAINT `recruiter_id`
    FOREIGN KEY (`recruiter_id`)
    REFERENCES `employment_agency_final`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`vacancy`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`vacancy` (
  `vacancy_id` INT NULL DEFAULT NULL AUTO_INCREMENT,
  `recruiter_id` INT NOT NULL,
  `published_date` DATE NOT NULL,
  `closed_date` DATE NOT NULL,
  `position` VARCHAR(20) NOT NULL,
  `job_description` VARCHAR(400) NOT NULL,
  `salary` VARCHAR(45) NOT NULL,
  `negotiable` BINARY NOT NULL,
  `requirements` VARCHAR(400) NOT NULL,
  `benefits` VARCHAR(400) NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`vacancy_id`, `recruiter_id`),
  UNIQUE INDEX (`vacancy_id` ASC) VISIBLE,
  INDEX `fk_vacancy_info_recruiter` (`recruiter_id` ASC) VISIBLE,
  CONSTRAINT `fk_vacancy_info_recruiter`
    FOREIGN KEY (`recruiter_id`)
    REFERENCES `employment_agency_final`.`recruiter` (`recruiter_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`job_application`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`job_application` (
  `seeker_id` INT NOT NULL,
  `vacancy_id` INT NOT NULL,
  PRIMARY KEY (`seeker_id`, `vacancy_id`),
  INDEX `fk_job_application_vacancy` (`vacancy_id` ASC) VISIBLE,
  CONSTRAINT `fk_job_application_vacancy`
    FOREIGN KEY (`vacancy_id`)
    REFERENCES `employment_agency_final`.`vacancy` (`vacancy_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_job_application_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency_final`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`vacancy_location`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`vacancy_location` (
  `vacancy_id` INT NOT NULL,
  `street_addr` VARCHAR(60) NOT NULL,
  `ward` VARCHAR(60) NOT NULL,
  `district` VARCHAR(60) NOT NULL,
  `city` VARCHAR(60) NOT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`street_addr`, `ward`, `district`, `city`, `vacancy_id`),
  INDEX `fk_vacancy_location_vacancy` (`vacancy_id` ASC) VISIBLE,
  CONSTRAINT `fk_vacancy_location_vacancy`
    FOREIGN KEY (`vacancy_id`)
    REFERENCES `employment_agency_final`.`vacancy` (`vacancy_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency_final`.`staff`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency_final`.`staff` (
  `staff_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`staff_id`),
  CONSTRAINT `FK_login_account_staff`
    FOREIGN KEY (`staff_id`)
    REFERENCES `employment_agency_final`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);

USE `employment_agency` ;

-- -----------------------------------------------------
-- Table `employment_agency`.`login_account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`login_account` (
  `id` INT NULL DEFAULT NULL,
  `email` VARCHAR(100) NOT NULL,
  `password` VARCHAR(100) NOT NULL,
  `user_type` VARCHAR(20) NOT NULL,
  `gender` VARCHAR(10) NULL DEFAULT NULL,
  `date_of_birth` DATE NULL DEFAULT NULL,
  `phone_number` CHAR(12) NULL DEFAULT NULL,
  `account_image` BLOB NULL DEFAULT NULL,
  `registration_date` DATE NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX (`id` ASC) VISIBLE,
  UNIQUE INDEX (`email` ASC) VISIBLE);


-- -----------------------------------------------------
-- Table `employment_agency`.`seeker`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`seeker` (
  `seeker_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `CV` LONGBLOB NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  UNIQUE INDEX (`seeker_id` ASC) VISIBLE,
  PRIMARY KEY (`seeker_id`),
  CONSTRAINT `FK_loginAccount_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`education_info`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`education_info` (
  `seeker_id` INT NOT NULL,
  `degree_name` VARCHAR(50) NOT NULL,
  `major` VARCHAR(50) NOT NULL,
  `school_name` VARCHAR(50) NOT NULL,
  `gpa` FLOAT NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`seeker_id`, `degree_name`, `major`, `school_name`),
  CONSTRAINT `fk_education_info_seeker_prof1`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`experience_info`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`experience_info` (
  `seeker_id` INT NOT NULL,
  `company_name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `work_address` VARCHAR(150) NULL DEFAULT NULL,
  `start_date` DATE NULL DEFAULT NULL,
  `end_date` DATE NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`seeker_id`, `company_name`, `job_title`),
  CONSTRAINT `fk_experience_info_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`location`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`location` (
  `location_id` INT NOT NULL AUTO_INCREMENT,
  `street_addr` VARCHAR(60) NOT NULL,
  `ward` VARCHAR(60) NOT NULL,
  `district` VARCHAR(60) NOT NULL,
  `city` VARCHAR(60) NOT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`location_id`),
  UNIQUE INDEX `idlocation_UNIQUE` (`location_id` ASC) VISIBLE);


-- -----------------------------------------------------
-- Table `employment_agency`.`recruiter`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`recruiter` (
  `recruiter_id` INT NOT NULL,
  `location_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `from_company` VARCHAR(100) NOT NULL,
  `company_description` VARCHAR(500) NOT NULL,
  `company_image` BLOB NULL DEFAULT NULL,
  `company_url` VARCHAR(60) NULL DEFAULT NULL,
  UNIQUE INDEX (`recruiter_id` ASC) VISIBLE,
  PRIMARY KEY (`recruiter_id`, `location_id`),
  INDEX `FK_recruiter_location_idx` (`location_id` ASC) VISIBLE,
  CONSTRAINT `FK_account_recruiter`
    FOREIGN KEY (`recruiter_id`)
    REFERENCES `employment_agency`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `FK_recruiter_location`
    FOREIGN KEY (`location_id`)
    REFERENCES `employment_agency`.`location` (`location_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`vacancy`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`vacancy` (
  `vacancy_id` INT NOT NULL AUTO_INCREMENT,
  `recruiter_id` INT NOT NULL,
  `location_id` INT NOT NULL,
  `published_date` DATE NOT NULL,
  `closed_date` DATE NOT NULL,
  `position` VARCHAR(20) NOT NULL,
  `job_description` VARCHAR(400) NOT NULL,
  `salary` VARCHAR(45) NOT NULL,
  `negotiable` BINARY NOT NULL,
  `requirements` VARCHAR(400) NOT NULL,
  `benefits` VARCHAR(400) NULL DEFAULT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`vacancy_id`, `recruiter_id`, `location_id`),
  UNIQUE INDEX (`vacancy_id` ASC) VISIBLE,
  INDEX `fk_vacancy_info_recruiter` (`recruiter_id` ASC) VISIBLE,
  INDEX `FK_vacancy_location_idx` (`location_id` ASC) VISIBLE,
  CONSTRAINT `fk_vacancy_info_recruiter`
    FOREIGN KEY (`recruiter_id`)
    REFERENCES `employment_agency`.`recruiter` (`recruiter_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `FK_vacancy_location`
    FOREIGN KEY (`location_id`)
    REFERENCES `employment_agency`.`location` (`location_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`job_application`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`job_application` (
  `seeker_id` INT NOT NULL,
  `vacancy_id` INT NOT NULL,
  PRIMARY KEY (`seeker_id`, `vacancy_id`),
  INDEX `fk_job_application_vacancy` (`vacancy_id` ASC) VISIBLE,
  CONSTRAINT `fk_job_application_vacancy`
    FOREIGN KEY (`vacancy_id`)
    REFERENCES `employment_agency`.`vacancy` (`vacancy_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_job_application_seeker`
    FOREIGN KEY (`seeker_id`)
    REFERENCES `employment_agency`.`seeker` (`seeker_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`staff_manager`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`staff_manager` (
  `manager_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `other_details` VARCHAR(200) NULL,
  PRIMARY KEY (`manager_id`),
  CONSTRAINT `FK_account_manager`
    FOREIGN KEY (`manager_id`)
    REFERENCES `employment_agency`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `employment_agency`.`staff`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`staff` (
  `staff_id` INT NOT NULL,
  `manager_id` INT NOT NULL,
  `name` VARCHAR(60) NOT NULL,
  `job_title` VARCHAR(50) NOT NULL,
  `other_details` VARCHAR(200) NULL DEFAULT NULL,
  PRIMARY KEY (`staff_id`, `manager_id`),
  INDEX `FK_manager_staff_idx` (`manager_id` ASC) VISIBLE,
  CONSTRAINT `FK_login_account_staff`
    FOREIGN KEY (`staff_id`)
    REFERENCES `employment_agency`.`login_account` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `FK_manager_staff`
    FOREIGN KEY (`manager_id`)
    REFERENCES `employment_agency`.`staff_manager` (`manager_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `employment_agency`.`vacancy_approval`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `employment_agency`.`vacancy_approval` (
  `staff_id` INT NOT NULL,
  `vacancy_id` INT NOT NULL,
  `approve_date` DATE NOT NULL,
  INDEX `fk_vacancy_approval_staff` (`staff_id` ASC) VISIBLE,
  INDEX `fk_vacancy_approval_vacancy` (`vacancy_id` ASC) VISIBLE,
  PRIMARY KEY (`staff_id`, `vacancy_id`),
  CONSTRAINT `fk_vacancy_approval_staff`
    FOREIGN KEY (`staff_id`)
    REFERENCES `employment_agency`.`staff` (`staff_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_vacancy_approval_vacancy`
    FOREIGN KEY (`vacancy_id`)
    REFERENCES `employment_agency`.`vacancy` (`vacancy_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
