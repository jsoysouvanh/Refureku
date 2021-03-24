#pragma once

#include "RefurekuGenerator/Properties/DefaultComplexPropertyRule.h"

class TestPropertyRule : public rfk::DefaultComplexPropertyRule
{
	protected:
		virtual std::string generateFileHeaderCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileHeaderData&	data)				const noexcept override;

		virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&			entity,
													   kodgen::ComplexProperty const&		property,
													   rfk::PropertyCodeGenPropertyAddData&	data)			const noexcept override;

		virtual std::string generatePostPropertyAddCode(kodgen::EntityInfo const&				entity,
														kodgen::ComplexProperty const&			property,
														rfk::PropertyCodeGenPropertyAddData&	data)		const noexcept override;

		virtual std::string generateClassFooterCode(kodgen::EntityInfo const&				entity,
													kodgen::ComplexProperty const&			property,
													rfk::PropertyCodeGenClassFooterData&	data)			const noexcept override;

		virtual std::string generateFileFooterCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileFooterData&	data)				const noexcept override;

	public:
		TestPropertyRule() noexcept;
};

class TestPropertyRule2 : public rfk::DefaultComplexPropertyRule
{
	protected:
		virtual std::string generateFileHeaderCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileHeaderData&	data)				const noexcept override;

		virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&			entity,
													   kodgen::ComplexProperty const&		property,
													   rfk::PropertyCodeGenPropertyAddData&	data)			const noexcept override;

		virtual std::string generatePostPropertyAddCode(kodgen::EntityInfo const&				entity,
														kodgen::ComplexProperty const&			property,
														rfk::PropertyCodeGenPropertyAddData&	data)		const noexcept override;

		virtual std::string generateClassFooterCode(kodgen::EntityInfo const&				entity,
													kodgen::ComplexProperty const&			property,
													rfk::PropertyCodeGenClassFooterData&	data)			const noexcept override;

		virtual std::string generateFileFooterCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileFooterData&	data)				const noexcept override;

	public:
		TestPropertyRule2() noexcept;
};

class TestPropertyRule3 : public rfk::DefaultComplexPropertyRule
{
	protected:
		virtual std::string generateFileHeaderCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileHeaderData&	data)				const noexcept override;

		virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&			entity,
													   kodgen::ComplexProperty const&		property,
													   rfk::PropertyCodeGenPropertyAddData&	data)			const noexcept override;

		virtual std::string generatePostPropertyAddCode(kodgen::EntityInfo const&				entity,
														kodgen::ComplexProperty const&			property,
														rfk::PropertyCodeGenPropertyAddData&	data)		const noexcept override;

		virtual std::string generateClassFooterCode(kodgen::EntityInfo const&				entity,
													kodgen::ComplexProperty const&			property,
													rfk::PropertyCodeGenClassFooterData&	data)			const noexcept override;

		virtual std::string generateFileFooterCode(kodgen::EntityInfo const&			entity,
												   kodgen::ComplexProperty const&		property,
												   rfk::PropertyCodeGenFileFooterData&	data)				const noexcept override;

	public:
		TestPropertyRule3() noexcept;
};