class RegistrationDateValidator < ActiveModel::Validator
	def validate(record)
	  if record.registration_start.present? && record.registration_end.present?
		if record.registration_end < record.registration_start
			record.errors.add :dates, ": registration end date cannot be before start date"
		end
		if record.registration_end == record.registration_start
			record.errors.add :dates, ": registration start time and end time must be different"
		end
		end
	end
  end