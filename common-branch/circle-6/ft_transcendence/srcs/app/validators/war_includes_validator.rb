class WarIncludesValidator < ActiveModel::Validator
	def validate(record)
	  if record.inc_friendly
		if !record.inc_easy && !record.inc_normal && !record.inc_hard
			record.errors.add :you, ": must select at least one difficulty and one max number of points"
		end
		if !record.inc_three && !record.inc_six && !record.inc_nine
			record.errors.add :you, ": must select at least one difficulty and one max number of points"
		end
	  end
	end
end