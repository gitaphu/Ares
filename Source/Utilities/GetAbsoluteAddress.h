// GetAbsoluteAddress

inline const uintptr_t GetAbsoluteAddress(uintptr_t pInstruction, int iOffset, int iSize) {
	return pInstruction + *reinterpret_cast<uint32_t*>(pInstruction + iOffset) + iSize;
};

template <typename T> inline T* GetAbsoluteAddress(uintptr_t pInstruction, int iOffset, int iSize) {
	return reinterpret_cast<T*>(pInstruction + *reinterpret_cast<uint32_t*>(pInstruction + iOffset) + iSize);
};
