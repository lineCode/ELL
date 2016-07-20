#pragma once
#include "Compiler.h"
#include "IRInclude.h"
#include "ScalarVar.h"
#include <stdio.h>

namespace emll
{
	namespace compiler
	{
		class IRCompiler : public Compiler
		{
		public:
			IRCompiler(const std::string& moduleName, std::ostream& os);

			virtual void Begin() override;
			virtual void End() override;

			llvm::Value* GetVariable(const std::string& name);
			llvm::Value* EnsureVariable(Variable& var);

			void DebugDump();

		public:
			void BeginMain(const std::string& functionName);
			virtual void BeginMain(const std::string& functionName, NamedValueTypeList& args) override;
			virtual void EndMain() override;
			virtual void Compile(LiteralNode& node) override;

			void RegisterFunctionArgs(NamedValueTypeList& args);

			llvm::Value* EmitScalar(Variable& var);

			llvm::Value* EmitLocalScalar(Variable& var);
			llvm::Value* EmitGlobalScalar(Variable& var);
			llvm::Value* EmitVectorRef(Variable& var);

			template<typename T>
			llvm::Value* EmitLocal(InitializedScalarVar<T>& var);
			template<typename T>
			llvm::Value* EmitRef(VectorRefScalarVar<T>& var);
			template<typename T>
			llvm::Value* EmitGlobal(InitializedScalarVar<T>& var);

		private:
			std::ostream& _os;
			IREmitter _emitter;
			IRModuleEmitter _module;
			IRFunctionEmitter _fn;
			IRVariableTable _vars;
			IRVariableTable _globals;
		};
	}
}

#include "../tcc/IRCompiler.tcc"