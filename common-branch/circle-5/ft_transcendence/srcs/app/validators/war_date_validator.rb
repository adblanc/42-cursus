class WarDateValidator < ActiveModel::Validator
	def validate(record)
	  if record.start.present? && record.end.present?
		if record.end < record.start
			record.errors.add :dates, ": end date cannot be before start date"
		end
		if record.end == record.start
			record.errors.add :dates, ": start time and end time must be different"
		end
		if record.war_times.first.present?
			self.check_wt(record)
		end
	  end
	end

	def check_wt(record)
		@wartimes = WarTime.where(war: record)
		for wt in @wartimes
			if wt.start < record.start || wt.start > record.end || wt.end < record.start || wt.end > record.end
				record.errors.add :wartime, 'must be set within the time frame of the war'
			end
		end
	end

  end