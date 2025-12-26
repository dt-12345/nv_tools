import dataclasses
from enum import auto, Enum, Flag
from typing import NamedTuple, TypeAlias

def parse_int(s: str) -> int:
    if s.startswith("0x"):
        return int(s, 16)
    elif s.startswith("0b"):
        return int(s, 2)
    elif s.endswith("U"):
        return int(s[:-1])
    return int(s)

# this scanner sucks lmao
class Scanner:
    __slots__ = ("stream", "pos", "line", "size")

    def __init__(self, stream: str):
        self.stream: str = stream
        self.pos: int = 0
        self.line: int = 1
        self.size: int = len(self.stream)

    def next_token(self, include_quotes: bool = False) -> str:
        start: int = -1
        in_quote: bool = False
        quote_type: str = ""
        while self.has_next():
            c: str = self.stream[self.pos]
            if c in ["\"", "'"]:
                if start != -1 and in_quote and c == quote_type:
                    if include_quotes:
                        token: str = self.stream[start:self.pos+1]
                    else:
                        token: str = self.stream[start:self.pos]
                    self.pos += 1
                    return token
                if c == quote_type:
                    in_quote = False
                    quote_type = ""
                elif not in_quote:
                    in_quote = True
                    quote_type = c
                if start == -1 and in_quote:
                    if include_quotes:
                        start = self.pos
                    else:
                        start = self.pos + 1
            elif c.isspace():
                if not in_quote and start != -1 and not in_quote:
                    return self.stream[start:self.pos]
                if c == "\n":
                    self.line += 1
            elif not c.isalpha() and not c.isnumeric() and c != "_":
                if not in_quote:
                    if start == -1:
                        token: str = self.stream[self.pos:self.pos+1]
                        self.pos += 1
                        return token
                    else:
                        return self.stream[start:self.pos]
            elif start == -1:
                start = self.pos
            self.pos += 1
        if start == -1:
            return None
        return self.stream[start:]

    def peek(self, pos: int, include_quotes: bool = False) -> str:
        old_pos: int = self.pos
        old_line: int = self.line
        self.pos = pos
        token: str = self.next_token(include_quotes)
        self.pos = old_pos
        self.line = old_line
        return token
    
    # probably would be better to just store the previous location and have a rewind option
    def peek_next(self, include_quotes: bool = False) -> str:
        return self.peek(self.pos, include_quotes)
    
    def at(self, pos: int) -> str:
        return self.stream[pos]

    def has_next(self) -> bool:
        return self.pos < self.size
    
    def assert_next(self, expected: str, msg: str = "", include_quotes: bool = False) -> None:
        tok: str = self.next_token(include_quotes)
        if tok != expected:
            raise ValueError(f"Line {self.line}: Expected {expected} but got {tok} instead!{f" {msg}" if msg else ""}")

@dataclasses.dataclass(slots=True)
class Register:
    name: str
    value: int
    group: "RegisterGroup"
@dataclasses.dataclass(slots=True)
class RegisterGroup:
    name: str
    values: dict[str, Register] = dataclasses.field(default_factory=dict)
    default: str | None = None
    is_composite: bool = False
    contained: set[str] = dataclasses.field(default_factory=set)

@dataclasses.dataclass(slots=True)
class TableEntry:
    value: int
    # can be a register, character literal, integer, or wildcard (represented by None here)
    arguments: list[Register | str | int | None] = dataclasses.field(default_factory=list)

@dataclasses.dataclass(slots=True)
class Table:
    name: str
    num_args: int
    lookup_type: int = 1
    entries: list[TableEntry] = dataclasses.field(default_factory=list)
    arg_types: list[RegisterGroup | type] = dataclasses.field(default_factory=list)

class BitRange(NamedTuple):
    start: int
    nbits: int

# TODO: whatever tf RegCluster is?
type Operand = "LiteralOperand | RegisterOperand | ImmediateOperand | UnitOperand | GroupOperand | PredicateOperand | OpcodeOperand | MemoryOperand"

# they distinguish between a bunch of different types of operator literals but I'm just gonna put them all together
@dataclasses.dataclass(slots=True)
class LiteralOperand:
    value: str

class OperandField(Flag):
    NOT = auto()        # @not, prepends !, [!]
    INVERT = auto()     # @invert, prepends ~, [~]
    NEGATE = auto()     # @negate, prepends -, [-]
    ABSOLUTE = auto()   # @absolute, prepends and appends |, [||]
    SIGN = auto()       # @sign, directly negates value, ???
    ABSVAL = auto()     # ???, directly takes absolute value, ???

@dataclasses.dataclass(slots=True)
class RegisterOperand:
    register: RegisterGroup
    name: str = ""
    fields: OperandField | None = None
    default: Register | None = None
    encoded: bool = False
    add_dot: bool = False # prepend . when printing
    always_print: bool = False
    is_predicate: bool = False

class ImmediateType(Enum):
    Integer = auto()
    Bitset = auto()
    F16 = auto()
    F32 = auto()
    F64 = auto()
    E6M9 = auto()
    BF16 = auto()
    TF32 = auto()

# numerical values like SImm, UImm, etc.
@dataclasses.dataclass(slots=True)
class ImmediateOperand:
    imm_type: ImmediateType
    bitwidth: int
    name: str = ""
    default: int | None = None
    fields: OperandField | None = None
    encoded: bool = False
    optional: bool = False
    always_print: bool = False
    signed: bool = False
    pcrel: bool = False
    signed_storage: bool = False

# { ... }
@dataclasses.dataclass(slots=True)
class UnitOperand:
    fields: list[Operand] = dataclasses.field(default_factory=list)

# $( ... )$ or /... /...
@dataclasses.dataclass(slots=True)
class GroupOperand:
    fields: list[Operand] = dataclasses.field(default_factory=list)

class PredicateFormatType(Enum):
    BRACKETS = 0    # [Predicate]
    PARENTHESES = 1 # (Predicate)
    ATSIGN = 2      # @Predicate

@dataclasses.dataclass(slots=True)
class PredicateOperand:
    register: RegisterOperand
    format: PredicateFormatType = PredicateFormatType.ATSIGN
    # qualifier? what is that

@dataclasses.dataclass(slots=True)
class OpcodeOperand:
    name: str = "Opcode"

@dataclasses.dataclass(slots=True)
class MemoryOperand:
    values: GroupOperand
    optional: bool = False

# type EncodableOperand is incompatible with isinstance
EncodableOperand: TypeAlias = OpcodeOperand | RegisterOperand | ImmediateOperand

class ReferenceType(Enum):
    XOR = auto()        # ??? (but presumably just the word)
    ROTATION = auto()   # ??? (but presumably just the word)
    BIAS = auto()       # ??? (but presumably just the word)
    INVERT = auto()     # ??? (but presumably just the word)
    NEGATE = auto()     # ??? (but presumably just the word)
    LOG2 = auto()       # ??? (but presumably just the word)
    SCALE = auto()      # SCALE
    MULTIPLY = auto()   # MULTIPLY
    # not explicitly encoded, based on the source field
    SIGN_EXT = auto()   # SSImm
    PCREL = auto()      # RSImm

class EncodingOp(NamedTuple):
    op_type: ReferenceType
    value: int

# represents EncodingField = SrcField; or EncodingField = Value;
@dataclasses.dataclass
class EncodingField:
    encoding: str = ""
    value: EncodableOperand | int | Register = 0
    field: OperandField | None = None
    ignored: bool = False
    encoding_ops: list[EncodingOp] = dataclasses.field(default_factory=list)

@dataclasses.dataclass
class Argument:
    value: EncodableOperand | int | Register | str = 0
    field: OperandField | None = None

# represents EncodingFields, ... = Table(Args, ...);
@dataclasses.dataclass
class MultiEncodingField:
    encodings: list[str] = dataclasses.field(default_factory=list)
    table: str = ""
    arguments: list[Argument] = dataclasses.field(default_factory=list)

@dataclasses.dataclass(slots=True)
class OperationClass:
    name: str
    is_alt: bool = False
    format: list[Operand] = dataclasses.field(default_factory=list)
    # conditions
    # properties
    # predicates
    opcodes: dict[str, int] = dataclasses.field(default_factory=dict)
    encodings: list[EncodingField | MultiEncodingField] = dataclasses.field(default_factory=list)
    # for convenience
    encodable_fields: dict[str, EncodableOperand] = dataclasses.field(default_factory=dict)
    encoded_fields: dict[str, EncodingField | MultiEncodingField] = dataclasses.field(default_factory=dict)

@dataclasses.dataclass(slots=True)
class FunctionalUnit:
    name: str = ""
    issue_slots: list[int] = dataclasses.field(default_factory=list)
    encoding_width: int = 64
    encodings: dict[str, list[BitRange]] = dataclasses.field(default_factory=dict)
    nop_encoding: list[EncodingField | MultiEncodingField] = dataclasses.field(default_factory=list)
    op_classes: dict[str, OperationClass] = dataclasses.field(default_factory=dict)

class DecodingMask(NamedTuple):
    mask: int
    value: int

class ValueRange(NamedTuple):
    min: int
    max: int

class EncodingRestriction(NamedTuple):
    encoding: EncodingField | MultiEncodingField
    ranges: list[ValueRange]

class DecodingInfo(NamedTuple):
    mask: DecodingMask
    restrictions: list[EncodingRestriction]
    opcode: str
    opclass: OperationClass

class RegisterComparator(NamedTuple):
    name: str
    value: int

class Architecture:
    def __init__(self) -> None:
        self.name: str = ""
        self.processor_id: str = ""
        self.issue_slots: int = 1
        self.word_size: int = 64
        self.branch_delay: int = 0
        self.elf_id: int = 0
        self.elf_abi: int = 0
        self.elf_abi_version: int = 0
        self.elf_version: int = 0
        self.options: list[str] = []
        self.rel_addr_base: int = 0 # idk if this is ever relative to something besides the current instruction, but assume it isn't
        self.empty_instr: str = ""
        self.conditions: dict[str, int] = { "INFO" : 2, "WARNING" : 3, "ERROR" : 5 }
        self.parameters: dict[str, int] = {}
        self.constants: dict[str, int] = {}
        self.register_groups: dict[str, RegisterGroup] = {} # some registers are only used as dummies so that they can print the operands properly
        self.tables: dict[str, Table] = {
            "IDENTICAL" : Table("IDENTICAL", 2, 0),
            "ARMExpandImm" : Table("ARMExpandImm", 3, 2),
            "FixLatSrcABCMap" : Table("FixLatSrcABCMap", 4, 5),
            "FixLatSrcABMap" : Table("FixLatSrcABMap", 3, 6),
            "FixLatSrcACMap" : Table("FixLatSrcACMap", 3, 7),
            "FixLatSrcAMap" : Table("FixLatSrcAMap", 2, 8),
            "FixLatSrcBMap" : Table("FixLatSrcBMap", 2, 9),
            "FixLatSrcMap" : Table("FixLatSrcMap", 1, 10),
            "ConstBankAddress0" : Table("ConstBankAddress0", 2, 11),
            "ConstBankAddress2" : Table("ConstBankAddress2", 2, 12),
        }
        self.op_properties: list[str] = []
        self.op_predicates: list[str] = []
        self.funit: FunctionalUnit = FunctionalUnit()

    def _read_property(self, scanner: Scanner) -> bool:
        name: str = scanner.next_token()
        val: str = scanner.next_token()
        match (name):
            case "PROCESSOR_ID":
                self.processor_id = val
            case "ISSUE_SLOTS":
                self.issue_slots = parse_int(val)
            case "WORD_SIZE":
                self.word_size = parse_int(val)
            case "BRANCH_DELAY":
                self.branch_delay = parse_int(val)
            case "ELF_ID":
                self.elf_id = parse_int(val)
            case "ELF_ABI":
                self.elf_abi = parse_int(val)
            case "ELF_ABI_VERSION":
                self.elf_abi_version = parse_int(val)
            case "ELF_VERSION":
                self.elf_version = parse_int(val)
        scanner.assert_next(";")
        return scanner.peek_next() != "RELOCATORS"

    def _read_list(self, scanner: Scanner, dest: list[str]) -> None:
        while (tok := scanner.next_token()) != ";":
            if tok != ",":
                dest.append(tok)

    def _read_rel_addr_base(self, scanner: Scanner) -> None:
        scanner.assert_next("CURRENT_INSTRUCTION")
        op: str = scanner.next_token()
        if op == "+":
            self.rel_addr_base = parse_int(scanner.next_token())
        elif op == "-":
            self.rel_addr_base = -parse_int(scanner.next_token())
        else:
            raise ValueError(f"Unknown format for RELATIVE_ADDRESS_BASE: {op}")
        scanner.assert_next(";")
    
    def _read_condition(self, scanner: Scanner) -> bool:
        name: str = scanner.next_token()
        scanner.assert_next(":")
        lvl_name: str = scanner.next_token()
        level: int
        if lvl_name in self.conditions:
            level = self.conditions[lvl_name]
        else:
            level = parse_int(lvl_name)
        self.conditions[name] = level
        return scanner.peek_next() != "PARAMETERS"
    
    def _read_named_values(self, scanner: Scanner, dest: dict[str, int], next_section_name: str) -> bool:
        name: str = scanner.next_token()
        scanner.assert_next("=")
        value: int = parse_int(scanner.next_token())
        dest[name] = value
        return scanner.peek_next() != next_section_name

    def _read_register(self, scanner: Scanner) -> bool:
        name: str = scanner.next_token()
        tokens: list[str] = []
        while (tok := scanner.next_token()) != ";":
            tokens.append(tok)
        reg: RegisterGroup = RegisterGroup(name)
        if tokens[0] == "=":
            reg.is_composite = True
            for t in tokens:
                if t in ["+", "="]:
                    continue
                reg.values.update(self.register_groups[t].values)
                reg.contained.update(reg.group.name for reg in reg.values.values())
                if self.register_groups[t].default is not None:
                    if reg.default is not None:
                        raise ValueError(f"Register group {reg.name} inherits multiple default values!")
                    reg.default = self.register_groups[t].default
        else:
            curr: int = 0
            i: int = 0
            num_tokens: int = len(tokens)
            while i < num_tokens:
                t: str = tokens[i]
                if t == ",":
                    i += 1
                    continue
                if i == num_tokens - 1:
                    reg.values[t] = Register(t, curr, reg)
                    curr += 1
                    i += 1
                elif tokens[i + 1] == "*":
                    reg.default = t
                    if i + 2 < num_tokens and tokens[i + 2] == "=":
                        curr = parse_int(tokens[i + 3])
                        reg.values[t] = Register(t, curr, reg)
                        curr += 1
                        i += 4
                    else:
                        reg.values[t] = Register(t, curr, reg)
                        curr += 1
                        i += 2
                elif tokens[i + 1] == "=":
                    curr = parse_int(tokens[i + 2])
                    reg.values[t] = Register(t, curr, reg)
                    curr += 1
                    i += 3
                elif tokens[i + 1] == "(":
                    # can ranged register values be defaults?
                    # I would imagine not since defaults are for unencoded but displayed operands
                    min_reg: int = parse_int(tokens[i + 2])
                    assert tokens[i + 3] == ".", tokens[i + 3]
                    assert tokens[i + 4] == ".", tokens[i + 4]
                    max_reg: int = parse_int(tokens[i + 5])
                    assert tokens[i + 6] == ")", tokens[i + 6]
                    if i + 7 < num_tokens and tokens[i + 7] == "=":
                        assert tokens[i + 8] == "(", tokens[i + 8]
                        min_val: int = parse_int(tokens[i + 9])
                        assert tokens[i + 10] == ".", tokens[i + 10]
                        assert tokens[i + 11] == ".", tokens[i + 11]
                        max_val: int = parse_int(tokens[i + 12])
                        assert tokens[i + 13] == ")", tokens[i + 13]
                        assert max_val - min_val == max_reg - min_reg, f"({min_reg}..{max_reg}) != ({min_val}..{max_val})"
                        curr = min_val
                        for j in range(min_reg, max_reg + 1):
                            reg.values[f"{t}{j}"] = Register(f"{t}{j}", curr, reg)
                            curr += 1
                        i += 14
                    else:
                        for j in range(min_reg, max_reg + 1):
                            reg.values[f"{t}{j}"] = Register(f"{t}{j}", curr, reg)
                            curr += 1
                        i += 7
                elif i + 1 < num_tokens and tokens[i + 1] == ".": # this is a hack to handle cases where there's a . in the name, not a real solution
                    reg_name: str = f"{t}{tokens[i + 1]}{tokens[i + 2]}"
                    reg.values[reg_name] = Register(reg_name, curr, reg)
                    curr += 1
                    i += 3
                else:
                    reg.values[t] = Register(t, curr, reg)
                    curr += 1
                    i += 1
        self.register_groups[name] = reg
        return scanner.peek_next() != "TABLES"

    def _count_args(self, tokens: list[str]) -> int:
        count: int = 0
        i: int = 0
        while i < len(tokens):
            count += 1
            if i + 1 < len(tokens) and tokens[i + 1] == "@":
                i += 3
            else:
                i += 1
        return count

    def _read_table(self, scanner: Scanner) -> bool:
        name: str = scanner.next_token()
        entries: list[list[str]] = []
        current_entry: list[str] = []
        line: int = scanner.line + 1
        while (tok := scanner.next_token(True)) != ";":
            if scanner.line != line:
                entries.append(current_entry.copy())
                current_entry = [tok]
                line = scanner.line
            else:
                current_entry.append(tok)
        if current_entry:
            entries.append(current_entry)
        assert len(entries) > 0, f"Line {scanner.line}: Encoding table {name} has no entries"
        table: Table = Table(name, self._count_args(entries[0]))
        for e in entries:
            entry: TableEntry = TableEntry(parse_int(e[-1].replace("_", "")))
            i: int = 0
            while i < len(e) - 1:
                t: str = e[i]
                if t == "-":
                    break
                if i + 1 < len(e) - 1 and e[i + 1] == "@":
                    entry.arguments.append(self.register_groups[t].values[e[i + 2].replace("\"", "")]) # registers with numeric names have to be quoted
                    i += 3
                elif t.startswith("'") and t.endswith("'"):
                    entry.arguments.append(t[1:-1])
                    i += 1
                else:
                    entry.arguments.append(parse_int(t))
                    i += 1
            table.entries.append(entry)
            if len(table.arg_types) == 0:
                table.arg_types = [type(arg) if not isinstance(arg, Register) else arg.group for arg in entry.arguments]
            else:
                assert len(entry.arguments) == len(table.arg_types), f"Line {scanner.line}: Argument count mismatch"
                for i, (expected, actual) in enumerate(zip(table.arg_types, (type(arg) if not isinstance(arg, Register) else arg.group for arg in entry.arguments))):
                    if isinstance(expected, RegisterGroup):
                        if actual is int:
                            assert any(entry.arguments[i] == r.value for r in expected.values.values()), f"Line {scanner.line}: Argument type mismatch: {table.arg_types} vs. {entry.arguments}"
                            for r in expected.values.values():
                                if r.value == entry.arguments[i]:
                                    entry.arguments[i] = r
                        else:
                            assert isinstance(actual, RegisterGroup), f"Line {scanner.line}: Argument type mismatch: {table.arg_types} vs. {entry.arguments}"
                            if expected.name != actual.name:
                                names: set[str]
                                if expected.is_composite:
                                    names = expected.contained.copy()
                                    names.add(actual.name)
                                else:
                                    names = {expected.name, actual.name}
                                matched: bool = False
                                for register in self.register_groups.values():
                                    if not register.is_composite:
                                        continue
                                    if register.contained.issuperset(names):
                                        table.arg_types[i] = register
                                        matched = True
                                        break
                                assert matched, f"Line {scanner.line}: Argument type mismatch: {table.arg_types} vs. {entry.arguments}"
                    else:
                        assert expected is actual, f"Line {scanner.line}: Argument type mismatch: {table.arg_types} vs. {entry.arguments}"
        self.tables[name] = table
        return scanner.peek_next() != "OPERATION"
    
    def _read_encoding_field(self, scanner: Scanner) -> bool:
        name: str = scanner.next_token()
        self.funit.encodings[name] = []
        mask: str = scanner.next_token()
        assert len(mask) == self.funit.encoding_width, f"Line {scanner.line}: Invalid encoding width for {name} - expected {self.funit.encoding_width} but got {len(mask)} ({mask})"
        curr_size: int = 0
        curr_start: int = -1
        for i, c in enumerate(reversed(mask)):
            if c == ".":
                if curr_start != -1:
                    self.funit.encodings[name].append(BitRange(curr_start, curr_size))
                    curr_size = 0
                    curr_start = -1
            elif c == "X":
                if curr_start == -1 or i == 0:
                    curr_start = i
                curr_size += 1
        if curr_start != -1:
            self.funit.encodings[name].append(BitRange(curr_start, curr_size))
        return scanner.peek_next() != "NOP_ENCODING"

    def _read_encoding(self, scanner: Scanner, opclass: OperationClass | None = None) -> list[EncodingField | MultiEncodingField]:
        encoding: list[EncodingField | MultiEncodingField] = []
        tokens: list[list[str]] = []
        current: list[str] = []
        line: int = -1
        while scanner.has_next() and scanner.peek_next() not in ["CLASS", "ALTERNATE"]:
            token: str = scanner.next_token()
            if token is None:
                break
            if line == -1:
                line = scanner.line
            if scanner.line != line:
                tokens.append(current.copy())
                current = [token]
                line = scanner.line
            else:
                current.append(token)
        if current:
            tokens.append(current)
        for group in tokens:
            if group[0] == "!":
                encoding.append(EncodingField(group[1], 0, ignored=True))
            else:
                if group[1] != "=":
                    pass
                if "(" in group:
                    i: int = group.index("=")
                    enc: MultiEncodingField = MultiEncodingField([e for e in group[:i] if e != ","], group[i + 1] if group[i + 1] != "*" else group[i + 2])
                    i += 1
                    if group[i] == "*":
                        i += 1
                    assert group[i + 1] == "(", f"Line {scanner.line}: Expected opening parenthesis but got {group[i]}"
                    assert group[-2] == ")", f"Line {scanner.line}: Expected closing parenthesis but got {group[-2]}"
                    i += 2
                    while i < len(group) - 2:
                        if group[i] in [",", ")"]:
                            i += 1
                        elif group[i + 1] in [",", ")"]:
                            # field or integer literal
                            try:
                                enc.arguments.append(Argument(parse_int(group[i])))
                            except:
                                assert opclass is not None, f"Line {scanner.line}: Cannot have references to operands without an opclass ({group})"
                                enc.arguments.append(Argument(opclass.encodable_fields[group[i]]))
                                opclass.encoded_fields[enc.arguments[-1].value.name] = enc
                            i += 1
                        elif group[i] == "`":
                            assert group[i + 2] == "@", f"Line {scanner.line}: Expected @ for register value"
                            enc.arguments.append(Argument(self.register_groups[group[i + 1]].values[group[i + 3]]))
                            i += 4
                        elif group[i + 1] == "@":
                            # specific field
                            assert opclass is not None, f"Line {scanner.line}: Cannot have references to operands without an opclass ({group})"
                            field: OperandField = {
                                "not" : OperandField.NOT,
                                "invert" : OperandField.INVERT,
                                "negate" : OperandField.NEGATE,
                                "absolute" : OperandField.ABSOLUTE,
                                "sign" : OperandField.SIGN,
                            }[group[i + 2]]
                            operand: EncodableOperand = opclass.encodable_fields[group[i]]
                            assert operand.fields is not None and field in operand.fields, f"Line {scanner.line}: {field} is not applicable for {group[i]}"
                            enc.arguments.append(Argument(operand, field))
                            for f in field:
                                fieldname: str = {
                                    OperandField.NOT : "not",
                                    OperandField.INVERT : "invert",
                                    OperandField.NEGATE : "negate",
                                    OperandField.ABSOLUTE : "absolute",
                                    OperandField.SIGN : "sign",
                                }[f]
                                opclass.encoded_fields[f"{operand.name}@{fieldname}"] = enc
                            i += 3
                        else:
                            # reference to existing field
                            assert opclass is not None, f"Line {scanner.line}: Cannot have references to operands without an opclass ({group})"
                            enc.arguments.append(Argument(opclass.encodable_fields[group[i]]))
                            opclass.encoded_fields[enc.arguments[-1].value.name] = enc
                            i += 1
                    encoding.append(enc)
                else:
                    assert group[1] == "=", f"Line {scanner.line}: Expected = after encoding name"
                    encoding_ops: list[str] = []
                    base: int = 2
                    if group[base] == "*": # what does the * mean in this case?
                        base += 1
                    if group[base] == "`":
                        # register
                        assert group[base + 2] == "@", f"Line {scanner.line}: Expected @"
                        encoding.append(EncodingField(group[0], self.register_groups[group[base + 1]].values[group[base + 3]]))
                        encoding_ops = group[base + 4:-1]
                    elif group[base + 1] == "@":
                        # operand field + modifier
                        assert opclass is not None, f"Line {scanner.line}: Cannot have references to operands without an opclass ({group})"
                        field: OperandField = {
                            "not" : OperandField.NOT,
                            "invert" : OperandField.INVERT,
                            "negate" : OperandField.NEGATE,
                            "absolute" : OperandField.ABSOLUTE,
                            "sign" : OperandField.SIGN,
                        }[group[base + 2]]
                        operand: EncodableOperand = opclass.encodable_fields[group[base]]
                        assert operand.fields is not None and field in operand.fields, f"Line {scanner.line}: {field} is not applicable for {group[base]}"
                        encoding.append(EncodingField(group[0], operand, field))
                        for f in field:
                            fieldname: str = {
                                OperandField.NOT : "not",
                                OperandField.INVERT : "invert",
                                OperandField.NEGATE : "negate",
                                OperandField.ABSOLUTE : "absolute",
                                OperandField.SIGN : "sign",
                            }[f]
                            opclass.encoded_fields[f"{operand.name}@{fieldname}"] = encoding[-1]
                        encoding_ops = group[base + 3:-1]
                        # add operand-dependent encoding ops
                        if isinstance(encoding[-1].field, ImmediateOperand):
                            if encoding[-1].field.signed_storage:
                                encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.SIGN_EXT))
                            if encoding[-1].field.pcrel:
                                encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.PCREL))
                    else:
                        # either a integer literal or a operand field
                        value: str = group[base]
                        try:
                            encoding.append(EncodingField(group[0], parse_int(value)))
                        except:
                            assert opclass is not None, f"Line {scanner.line}: Cannot have references to operands without an opclass ({group})"
                            encoding.append(EncodingField(group[0], opclass.encodable_fields[value]))
                            opclass.encoded_fields[encoding[-1].value.name] = encoding[-1]
                            # add operand-dependent encoding ops
                            if isinstance(encoding[-1].field, ImmediateOperand):
                                if encoding[-1].field.signed_storage:
                                    encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.SIGN_EXT))
                                if encoding[-1].field.pcrel:
                                    encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.PCREL))
                        encoding_ops = group[base + 1:-1]
                    i: int = 0
                    while i < len(encoding_ops):
                        if encoding_ops[i] == "MULTIPLY":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.MULTIPLY, parse_int(encoding_ops[i + 1])))
                            i += 2
                        elif encoding_ops[i] == "SCALE":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.SCALE, parse_int(encoding_ops[i + 1])))
                            i += 2
                        elif encoding_ops[i] == "BIAS":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.BIAS, parse_int(encoding_ops[i + 1])))
                            i += 2
                        elif encoding_ops[i] == "ROR":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.ROTATION, parse_int(encoding_ops[i + 1])))
                            i += 2
                        elif encoding_ops[i] == "EXOR":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.XOR, parse_int(encoding_ops[i + 1])))
                            i += 2
                        elif encoding_ops[i] == "LOG2":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.LOG2))
                            i += 1
                        elif encoding_ops[i] == "NEGATE":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.NEGATE))
                            i += 1
                        elif encoding_ops[i] == "INVERT":
                            encoding[-1].encoding_ops.append(EncodingOp(ReferenceType.INVERT))
                            i += 1
                        else:
                            raise ValueError(f"Line {scanner.line}: Unknown reference type: {encoding_ops[i]}")
                    if isinstance(encoding[-1].value, OpcodeOperand):
                        assert len(encoding[-1].encoding_ops) == 0, f"Line {scanner.line}: Reference operations are not permitted for opcode encoding"
        return encoding
    
    def _read_register_operand(self, scanner: Scanner) -> RegisterOperand:
        group: str = scanner.next_token()
        assert group in self.register_groups, f"Line {scanner.line}: Register group {group} does not exist"
        operand: RegisterOperand = RegisterOperand(self.register_groups[group])
        token: str = scanner.next_token()
        if token == "(":
            operand.default = operand.register.values[scanner.next_token()]
            token = scanner.next_token()
            if token == "/":
                scanner.assert_next("PRINT")
                operand.always_print = True
                token = scanner.next_token()
            assert token == ")", f"Line {scanner.line}: Expected closing parenthesis"
            token = scanner.next_token()
        else:
            if operand.register.default is not None:
                operand.default = operand.register.values[operand.register.default]
        encoded: bool = True
        if token == "@":
            encoded = False
            token = scanner.next_token() # TODO: check if there's required to be another token here or not
        if token == ":":
            operand.encoded = encoded
            operand.name = scanner.next_token()
            # hack for names with .
            # this is just a limitation of the shitty scanner - I should really just write a proper lexer
            if scanner.peek_next() == ".":
                operand.name = f"{operand.name}{scanner.next_token()}{scanner.next_token()}"
        else:
            raise ValueError(f"Line {scanner.line}: Unexpected token: {token}")
        return operand

    def _read_predicate_operand(self, scanner: Scanner) -> PredicateOperand:
        scanner.assert_next("PREDICATE")
        format_char: str = scanner.next_token()
        format: PredicateFormatType
        if format_char == "@":
            format = PredicateFormatType.ATSIGN
        elif format_char == "(":
            format = PredicateFormatType.PARENTHESES
        elif format_char == "[":
            format = PredicateFormatType.BRACKETS
        else:
            raise ValueError(f"Line {scanner.line}: Unknown predicate format: {format}")
        register: Operand | None = self._read_format_argument(scanner)
        if not isinstance(register, RegisterOperand):
            raise ValueError(f"Line {scanner.line}: Predicates must be registers")
        operand: PredicateOperand = PredicateOperand(register, format)
        operand.register.is_predicate = True
        return operand
    
    def _read_opcode_operand(self, scanner: Scanner) -> OpcodeOperand:
        scanner.assert_next("Opcode")
        return OpcodeOperand()
    
    def _read_dotted_unit_operand(self, scanner: Scanner) -> UnitOperand:
        operand: UnitOperand = UnitOperand()
        while True:
            scanner.assert_next("/")
            operand.fields.append(self._read_register_operand(scanner))
            if not scanner.peek_next() == "/":
                break
        for field in operand.fields:
            field.add_dot = True
        return operand
    
    def _read_group_operand(self, scanner: Scanner) -> GroupOperand:
        scanner.assert_next("$"), scanner.assert_next("(")
        operand: GroupOperand = GroupOperand()
        while True:
            operand.fields.append(self._read_format_argument(scanner))
            if scanner.peek_next() == ")":
                break
        scanner.assert_next(")"), scanner.assert_next("$")
        return operand
    
    def _read_unit_operand(self, scanner: Scanner) -> UnitOperand:
        scanner.assert_next("{")
        operand: UnitOperand = UnitOperand()
        while True:
            operand.fields.append(self._read_format_argument(scanner))
            if scanner.peek_next() == "}":
                break
        scanner.assert_next("}")
        return operand

    def _read_memory_operand(self, scanner: Scanner) -> MemoryOperand:
        scanner.assert_next("[")
        values: GroupOperand = GroupOperand()
        while True:
            values.fields.append(self._read_format_argument(scanner))
            next: str = scanner.next_token()
            if next == "+": # can this be a -?
                continue
            elif next == "]":
                break
            else:
                raise ValueError(f"Line {scanner.line}: Unexpected token {next}")
        if scanner.peek_next() == "*":
            return MemoryOperand(values, scanner.next_token() == "*")
        return MemoryOperand(values)
    
    def _read_immediate_operand(self, scanner: Scanner) -> ImmediateOperand:
        token: str = scanner.next_token()
        imm_type: ImmediateType = {
            "UImm" : ImmediateType.Integer,
            "SImm" : ImmediateType.Integer,
            "SSImm" : ImmediateType.Integer,
            "RSImm" : ImmediateType.Integer,
            "BITSET" : ImmediateType.Bitset,
            "F16Imm" : ImmediateType.F16,
            "F32Imm" : ImmediateType.F32,
            "F64Imm" : ImmediateType.F64,
            "E6M9Imm" : ImmediateType.E6M9,
            "E8M7Imm" : ImmediateType.BF16,
            "E8M10Imm" : ImmediateType.TF32,
        }[token]
        scanner.assert_next("(")
        num_bits: int = parse_int(scanner.next_token())
        operand: ImmediateOperand = ImmediateOperand(imm_type, num_bits)
        operand.pcrel = token == "RSImm"
        operand.signed = token.endswith("SImm")
        operand.signed_storage = token == "SSImm"
        operand.fields = OperandField.SIGN if token.endswith("SImm") else None
        while (token := scanner.next_token()) != ")":
            if token == "/":
                next: str = scanner.next_token()
                if next == "PRINT":
                    operand.always_print = True
                else:
                    operand.default = parse_int(next)
                    if scanner.peek_next() == "*":
                        operand.optional = scanner.next_token() != "*"
            else:
                raise ValueError(f"Line {scanner.line}: Unexpected token: {token}")
        token = scanner.peek_next()
        if token == "*": # what does this do?
            scanner.next_token()
            token = scanner.peek_next()
        encoded: bool = True
        if token == "@":
            encoded = scanner.next_token() != "@"
            token = scanner.peek_next()
        if token == ":":
            scanner.assert_next(":")
            operand.name = scanner.next_token()
        operand.encoded = encoded
        return operand
    
    def _read_operand_fields(self, scanner: Scanner) -> OperandField:
        fields: OperandField = OperandField(0)
        while True:
            scanner.assert_next("[")
            t: str = scanner.next_token()
            fields |= {
                "!" : OperandField.NOT,
                "~" : OperandField.INVERT,
                "-" : OperandField.NEGATE,
                "|" : OperandField.ABSOLUTE,
            }[t]
            if t == "|":
                scanner.assert_next("|")
            scanner.assert_next("]")
            if scanner.peek_next() != "[":
                break
        return fields

    def _read_format_argument(self, scanner: Scanner) -> Operand | None:
        match (scanner.peek_next()):
            case "PREDICATE":
                return self._read_predicate_operand(scanner)
            case "Opcode":
                return self._read_opcode_operand(scanner)
            case "/":
                return self._read_dotted_unit_operand(scanner)
            case "$":
                return self._read_group_operand(scanner)
            case "{":
                return self._read_unit_operand(scanner)
            case "[":
                old_pos: int = scanner.pos
                old_line: int = scanner.line
                scanner.next_token()
                next: str = scanner.next_token()
                scanner.pos = old_pos
                scanner.line = old_line
                if next in ["!", "~", "-", "|"]:
                    fields: OperandField = self._read_operand_fields(scanner)
                    operand: Operand | None = self._read_format_argument(scanner)
                    if not isinstance(operand, RegisterOperand) and not isinstance(operand, ImmediateOperand):
                        raise ValueError(f"Line {scanner.line}: Expected register or immediate following operand fields")
                    if operand.fields is None:
                        operand.fields = fields
                    else:
                        operand.fields |= fields
                    return operand
                else:
                    return self._read_memory_operand(scanner)
            case "UImm" | "SImm" | "SSImm" | "RSImm" | "BITSET" | "F16Imm" | "F32Imm" | "F64Imm" | "E6M9Imm" | "E8M7Imm" | "E8M10Imm":
                return self._read_immediate_operand(scanner)
            case "," | "=" | ":" | "?" | "/" | "^" | "&" | "<<":
                return LiteralOperand(scanner.next_token())
            case ";":   # end of format
                return None
            case _:     # otherwise it's probably a register
                return self._read_register_operand(scanner)
    
    def get_encodable_fields(self, op: Operand, exclude_unencoded: bool = True) -> list[EncodableOperand]:
        if isinstance(op, EncodableOperand):
            if isinstance(op, OpcodeOperand) or op.encoded or not exclude_unencoded:
                return [op]
            return []
        elif isinstance(op, UnitOperand) or isinstance(op, GroupOperand):
            return [inner_op for outer_op in op.fields for inner_op in self.get_encodable_fields(outer_op)]
        elif isinstance(op, PredicateOperand):
            return self.get_encodable_fields(op.register)
        elif isinstance(op, MemoryOperand):
            return [inner_op for outer_op in op.values.fields for inner_op in self.get_encodable_fields(outer_op)]
        else:
            return []

    def _read_opclass(self, scanner: Scanner) -> bool:
        alt: bool = False
        token: str = scanner.next_token()
        if token == "ALTERNATE":
            alt = True
            token = scanner.next_token()
        assert token == "CLASS", f"Line {scanner.line}: Expected CLASS but got {token}"
        opclass: OperationClass = OperationClass(scanner.next_token(), alt)
        scanner.assert_next("FORMAT")
        while True:
            operand: Operand | None = self._read_format_argument(scanner)
            if operand is None:
                break
            opclass.format.append(operand)
        for field in opclass.format:
            for op in self.get_encodable_fields(field):
                if isinstance(op, OpcodeOperand):
                    opclass.encodable_fields["Opcode"] = op
                else:
                    opclass.encodable_fields[op.name] = op
                    if isinstance(op, RegisterOperand):
                        # it seems it's possible for the encoding to specify an occurrence index so this check isn't entirely accurate
                        # but I've also not seen it used so I don't know how it would be specified so this suffices for now
                        if op.register.name not in opclass.encodable_fields:
                            opclass.encodable_fields[op.register.name] = op
        # skip conditions, properties, and predicates bc I'm too lazy to figure out how best to represent them since they include expressions
        while scanner.next_token() != "OPCODES": pass
        while (token := scanner.next_token()) != "ENCODING":
            scanner.assert_next("=")
            opclass.opcodes[token] = parse_int(scanner.next_token())
            scanner.assert_next(";")
        opclass.encodings = self._read_encoding(scanner, opclass)
        self.funit.op_classes[opclass.name] = opclass
        return scanner.has_next()

    def _read_functional_unit(self, scanner: Scanner) -> None:
        self.funit.name = scanner.next_token()
        scanner.assert_next("ISSUE_SLOTS")
        while (tok := scanner.next_token()) != ";":
            self.funit.issue_slots.append(parse_int(tok))
        scanner.assert_next("ENCODING"), scanner.assert_next("WIDTH")
        self.funit.encoding_width = parse_int(scanner.next_token())
        scanner.assert_next(";")
        while self._read_encoding_field(scanner): pass
        scanner.assert_next("NOP_ENCODING")
        self.funit.nop_encoding = self._read_encoding(scanner)
        while self._read_opclass(scanner): pass
    
    def get_encoding_mask(self, ranges: list[BitRange], encoded_value: int) -> DecodingMask:
        mask: int = 0
        value: int = 0
        bit_offset: int = 0
        for r in ranges:
            bitmask: int = (1 << r.nbits) - 1
            mask |= bitmask << r.start
            value = (encoded_value >> bit_offset & bitmask) << r.start | (value & ~(bitmask << r.start))
            bit_offset += r.nbits
        return DecodingMask(mask, value)

    # char literals are technically also supported but I don't think those are ever used?
    def _reverse_table_lookup(self, values: list[int | Register], table: Table) -> int:
        if len(values) != table.num_args:
            raise ValueError(f"Table {table.name} expects {table.num_args} arguments but got {len(values)} arguments instead! ({values})")
        if table.lookup_type != 1:
            raise ValueError(f"Only lookup type 1 supports constant time lookup! {table.name}: {table.lookup_type}")
        for entry in table.entries:
            if entry.arguments == values:
                return entry.value
        raise ValueError(f"No matching entry in table {table.name} for {values}")

    def _calc_decoding_mask(self, opclass: OperationClass, opcode: str) -> DecodingMask:
        mask: int = 0
        value: int = 0
        for encoding in opclass.encodings:
            if isinstance(encoding, EncodingField):
                if encoding.ignored or len(encoding.encoding_ops) > 0:
                    continue
                encoded_value: int
                if isinstance(encoding.value, OpcodeOperand):
                    encoded_value = opclass.opcodes[opcode]
                elif isinstance(encoding.value, int):
                    encoded_value = encoding.value
                elif isinstance(encoding.value, Register):
                    encoded_value = encoding.value.value
                else:
                    continue
                m, v = self.get_encoding_mask(self.funit.encodings[encoding.encoding], encoded_value)
                mask |= m
                value |= v
            else:
                if any(not isinstance(arg.value, int) and not isinstance(arg.value, Register) for arg in encoding.arguments):
                    continue
                assert len(encoding.encodings) == 1, f"Table lookup type 1 only supports a single encoded value! Got {len(encoding.encodings)} values instead"
                m, v = self.get_encoding_mask(self.funit.encodings[encoding.encodings[0]], self._reverse_table_lookup([arg.value for arg in encoding.arguments], encoding.table))
                mask |= m
                value |= v
        return DecodingMask(mask, value)
    
    def _calc_value_restrictions(self, values: list[int]) -> list[ValueRange]:
        values = sorted(set(values))
        start: int | None = None
        prev: int | None = None
        ranges: list[ValueRange] = []
        for value in values:
            if start is None:
                start = value
            elif prev is not None:
                if value - prev != 1: # break in values
                    ranges.append(ValueRange(start, prev + 1))
                    start = value
            else:
                raise ValueError("How did you get here")
            prev = value
        ranges.append(ValueRange(start, value + 1))
        return ranges
    
    def _calc_encoding_restrictions(self, opclass: OperationClass) -> list[EncodingRestriction]:
        restrictions: list[EncodingRestriction] = []
        for encoding in opclass.encodings:
            if isinstance(encoding, MultiEncodingField):
                table: Table = self.tables[encoding.table]
                if table.lookup_type == 1:
                    restrictions.append(EncodingRestriction(encoding, self._calc_value_restrictions([entry.value for entry in table.entries])))
            else:
                if encoding.ignored or isinstance(encoding.value, RegisterOperand) and len(encoding.encoding_ops) > 0:
                    continue
                if isinstance(encoding.value, RegisterOperand):
                    if encoding.field is None:
                        restrictions.append(EncodingRestriction(encoding, self._calc_value_restrictions([r.value for r in encoding.value.register.values.values()])))
                    else:
                        restrictions.append(EncodingRestriction(encoding, [ValueRange(0, 2)]))
                elif isinstance(encoding.value, ImmediateOperand):
                    if encoding.field is None:
                        if encoding.value.bitwidth < 32:
                            restrictions.append(EncodingRestriction(encoding, [ValueRange(0, 1 << encoding.value.bitwidth)]))
                    else:
                        restrictions.append(EncodingRestriction(encoding, [ValueRange(0, 2)]))
        return restrictions

    # generate masks and masked values for each opclass
    # masks should be sorted in order from most
    # masks should include:
    # - opcode
    # - constant encoding integer values
    # - constant encoding register values
    # - constant encoding values derived from tables
    # each opclass has multiple opcodes but they all have the same value usually so the last one ends up overwriting the others
    def get_opclass_decoding_info(self, opclass: OperationClass) -> list[DecodingInfo]:
        info: dict[str, DecodingMask] = {}
        for opcode, value in opclass.opcodes.items():
             # the duplicates will overwrite each other which is intended
            info[value] = DecodingInfo(self._calc_decoding_mask(opclass, opcode), self._calc_encoding_restrictions(opclass), opcode, opclass)
        return list(info.values())
    
    def get_used_tables(self) -> list[str]:
        tables: set[str] = set()
        for opclass in self.funit.op_classes.values():
            for encoding in opclass.encodings:
                if isinstance(encoding, MultiEncodingField):
                    tables.add(encoding.table)
        return sorted(tables)
    
    def get_used_registers(self) -> list[str]:
        registers: set[str] = set()
        for opclass in self.funit.op_classes.values():
            for encoding in opclass.encodings:
                if isinstance(encoding, EncodingField):
                    if isinstance(encoding.value, Register):
                        registers.add(encoding.value.group.name)
                        if encoding.value.group.is_composite:
                            registers.update(encoding.value.group.contained)
                    elif isinstance(encoding.value, RegisterOperand):
                        registers.add(encoding.value.register.name)
                        if encoding.value.register.is_composite:
                            registers.update(encoding.value.register.contained)
                else:
                    for arg_type in self.tables[encoding.table].arg_types:
                        if isinstance(arg_type, RegisterGroup):
                            registers.add(arg_type.name)
                            if arg_type.is_composite:
                                registers.update(arg_type.contained)
            for op in opclass.format:
                for field in self.get_encodable_fields(op, True):
                    if isinstance(field, RegisterOperand):
                        registers.add(field.register.name)
                        if field.register.is_composite:
                            registers.update(field.register.contained)
        return sorted(registers, key=lambda name: (self.register_groups[name].is_composite, name))

    def get_used_encodings(self) -> list[str]:
        encodings: set[str] = set()
        for opclass in self.funit.op_classes.values():
            for encoding in opclass.encodings:
                if isinstance(encoding, EncodingField):
                    if not encoding.ignored:
                        encodings.add(encoding.encoding)
                else:
                    encodings.update(encoding.encodings)
        return sorted(encodings)

    # I have no idea what the exact grammar of this format is, they completely fucked the formatting (shitty obfuscation???)
    @classmethod
    def load(cls, machine_description: str) -> "Architecture":
        arch: Architecture = cls()
        scanner: Scanner = Scanner(machine_description)
        scanner.assert_next("ARCHITECTURE")
        arch.name = scanner.next_token()
        if scanner.peek_next() != "RELOCATORS":
            while arch._read_property(scanner): pass
        scanner.assert_next("RELOCATORS")
        # idc about the relocators so we'll just skip them
        while scanner.next_token() != ";": pass
        scanner.assert_next("OPTIONS")
        arch._read_list(scanner, arch.options)
        scanner.assert_next("RELATIVE_ADDRESS_BASE")
        arch._read_rel_addr_base(scanner)
        scanner.assert_next("EMPTY_INSTRUCTION"), scanner.assert_next("=")
        arch.empty_instr = scanner.next_token()
        scanner.assert_next(";")
        scanner.assert_next("CONDITION"), scanner.assert_next("TYPES")
        while arch._read_condition(scanner): pass
        scanner.assert_next("PARAMETERS")
        while arch._read_named_values(scanner, arch.parameters, "CONSTANTS"): pass
        scanner.assert_next("CONSTANTS")
        while arch._read_named_values(scanner, arch.constants, "REGISTERS"): pass
        scanner.assert_next("REGISTERS")
        try:
            while arch._read_register(scanner): pass
        except Exception as e:
            raise ValueError(f"Line {scanner.line}: {e}") from e
        scanner.assert_next("TABLES")
        while arch._read_table(scanner): pass
        scanner.assert_next("OPERATION"), scanner.assert_next("PROPERTIES")
        arch._read_list(scanner, arch.op_properties)
        scanner.assert_next("OPERATION"), scanner.assert_next("PREDICATES")
        arch._read_list(scanner, arch.op_predicates)
        scanner.assert_next("FUNIT")
        arch._read_functional_unit(scanner)
        return arch

def fix_name(name: str) -> str:
    if name[0].isdigit():
        name = f"_{name}"
    return name.replace(".", "_").replace(" ", "_")

def write_file(include_path: str, source_path: str, arch: Architecture) -> None:
    decoding_info: list[DecodingInfo] = [
        e for opclass in arch.funit.op_classes for e in arch.get_opclass_decoding_info(arch.funit.op_classes[opclass])
    ]
    decoding_info.sort(key=lambda i: i.mask.mask.bit_count(), reverse=True)
    # none of this is required but I don't feel like handling other cases rn
    assert len(arch.funit.nop_encoding) == 1 and isinstance(arch.funit.nop_encoding[0], EncodingField) and isinstance(arch.funit.nop_encoding[0].value, int)
    nop: DecodingMask = arch.get_encoding_mask(arch.funit.encodings[arch.funit.nop_encoding[0].encoding], arch.funit.nop_encoding[0].value)

    with open(os.path.join(include_path, f"{arch.name}.hpp"), "w", encoding="utf-8") as header:
        header.write("#pragma once\n\n")
        header.write("#include \"utility.hpp\"\n\n")
        header.write("#include <cstdint>\n")
        header.write("#include <optional>\n")
        header.write("#include <tuple>\n")
        header.write("#include <type_traits>\n")
        header.write("#include <variant>\n\n")
        header.write(f"namespace {arch.name} {{\n\n")
        header.write("enum class OpClass : std::uint32_t {\n")
        for i, opclass in enumerate(arch.funit.op_classes):
            header.write(f"  {fix_name(opclass):<25} = {i:>#5x}, // {opclass}\n")
        header.write(f"  {"NOP_DEFAULT":<25} = {len(arch.funit.op_classes):>#5x}, // NOP\n")
        header.write("};\n\n")
        header.write("struct DecodedInstruction {\n")
        header.write("  std::uint64_t inst;\n")
        header.write("  std::uint64_t sched;\n")
        header.write("  const char* opcode;\n")
        header.write("  OpClass opclass;\n")
        header.write("};\n\n")
        header.write("std::optional<const DecodedInstruction> Decode(std::uint64_t inst, std::uint64_t sched);\n\n")
        header.write(f"#define MAX_CONST_BANK {arch.parameters["MAX_CONST_BANK"]}\n\n")
        header.write(f"#define RELATIVE_ADDRESS_BASE {arch.rel_addr_base}ull\n\n")
        for encoding in arch.get_used_encodings():
            enc: list[BitRange] = arch.funit.encodings[encoding]
            if all(r.start < 64 for r in enc):
                header.write(f"using {fix_name(encoding)}Encoding = Encoding<{", ".join(f"BitRange<{r.start}, {r.nbits}>" for r in enc)}>;\n")
            elif all(r.start >= 64 for r in enc):
                header.write(f"using {fix_name(encoding)}Encoding = Encoding<{", ".join(f"BitRange<{r.start - 64}, {r.nbits}>" for r in enc)}>;\n")
            else:
                raise Exception(enc, encoding) # I'm too lazy to handle this case
        header.write("\n")
        seen_registers: dict[tuple[RegisterComparator, ...], str] = {}
        for register in arch.get_used_registers():
            reg: RegisterGroup = arch.register_groups[register]
            if reg.is_composite:
                registers: set[str] = set(v.group.name for v in reg.values.values())
                if len(registers) == 1:
                    header.write(f"using {fix_name(register)} = {fix_name(list(registers)[0])};\n")
                else:
                    types: list[str] = sorted(
                        set(v.group.name for v in reg.values.values()), key=lambda name: min(r.value for r in arch.register_groups[name].values.values())
                    )
                    header.write(f"struct {fix_name(register)} {{\n")
                    header.write("  std::uint32_t raw;\n")
                    header.write(f"  constexpr {fix_name(register)}(std::uint32_t _raw) noexcept : raw(_raw) {{}}\n")
                    header.write("  constexpr operator std::uint32_t() const { return raw; }\n")
                    for r in types:
                        header.write(f"  constexpr {fix_name(register)}({fix_name(r)} _raw) noexcept : raw(static_cast<std::uint32_t>(_raw)) {{}}\n")
                        header.write(f"  constexpr explicit operator {fix_name(r)}() const {{ return static_cast<{fix_name(r)}>(raw); }}\n")
                    header.write("};\n")
            else:
                reg_key: tuple[RegisterComparator, ...] = tuple(RegisterComparator(name, value.value) for name, value in sorted(reg.values.items(), key=lambda i: (i[1].value, i[0])))
                if reg_key in seen_registers:
                    header.write(f"using {fix_name(register)} = {fix_name(seen_registers[reg_key])};\n")
                else:
                    seen_registers[reg_key] = reg.name
                    header.write(f"enum class {fix_name(register)} : std::uint32_t {{\n")
                    max_name = max(len(n) for n in reg.values)
                    for value, r in sorted(reg.values.items(), key=lambda i: (i[1].value, i[1].name)):
                        fixed_name: str = fix_name(value)
                        if fixed_name != value and fixed_name in reg.values:
                            assert reg.values[value].value == reg.values[fix_name(value)].value
                        else:
                            header.write(f"  {fix_name(value):<{max_name+1}} = {r.value:<#8x}, // {value}\n")
                    header.write("};\n")
        for table in arch.get_used_tables():
            tbl: Table = arch.tables[table]
            if tbl.lookup_type == 1:
                types: str = ", ".join(fix_name(v.name) if isinstance(v, RegisterGroup) else "std::uint64_t" for v in tbl.arg_types)
                header.write(f"std::optional<std::tuple<{types}>> {fix_name(tbl.name)}(std::uint64_t value);\n")
            elif tbl.lookup_type == 0: # IDENTICAL
                header.write("template<typename T>\n")
                header.write(f"std::optional<std::tuple<T, T>> {fix_name(tbl.name)}(std::uint64_t value) {{\n")
                header.write("  static_assert(std::is_integral_v<T> || std::is_nothrow_convertible_v<std::uint64_t, T>, \"T must be an integral type!\");\n")
                header.write("  return std::make_optional<std::tuple<T, T>>(static_cast<T>(value), static_cast<T>(value));\n")
                header.write("}\n")
            elif tbl.lookup_type == 11: # ConstBankAddress0
                header.write("template<std::size_t BitSize>\n")
                header.write(f"std::optional<std::tuple<std::uint64_t, std::int64_t>> {fix_name(tbl.name)}(std::uint64_t value) {{\n")
                header.write("  static_assert(BitSize <= sizeof(std::uint64_t) * CHAR_BIT, \"Constant bank offset must fit within a 64-bit integer!\");\n")
                header.write("  constexpr std::size_t nbits = BitSize - 1;\n")
                header.write("  constexpr std::uint64_t mask = (1ull << nbits) - 1;\n")
                header.write("  const std::uint64_t slot = value >> nbits;\n")
                header.write("  const std::int64_t offset = SEXT<nbits>(value & mask);\n")
                header.write("  return slot > MAX_CONST_BANK ? std::nullopt : std::make_optional<std::tuple<std::uint64_t, std::int64_t>>(slot, offset);\n")
                header.write("}\n")
            elif tbl.lookup_type == 12: # ConstBankAddress2
                header.write("template<std::size_t BitSize>\n")
                header.write(f"std::optional<std::tuple<std::uint64_t, std::int64_t>> {fix_name(tbl.name)}(std::uint64_t value) {{\n")
                header.write("  static_assert(BitSize <= sizeof(std::uint64_t) * CHAR_BIT, \"Constant bank offset must fit within a 64-bit integer!\");\n")
                header.write("  constexpr std::size_t nbits = BitSize - 1;\n")
                header.write("  constexpr std::uint64_t mask = (1ull << nbits) - 1;\n")
                header.write("  const std::uint64_t slot = value * 4 >> nbits;\n")
                header.write("  const std::int64_t offset = SEXT<nbits>(value * 4 & mask);\n")
                header.write("  return slot > MAX_CONST_BANK ? std::nullopt : std::make_optional<std::tuple<std::uint64_t, std::int64_t>>(slot, offset);\n")
                header.write("}\n")
        header.write("\n")
        header.write(f"}} // namespace {arch.name}")

    with open(os.path.join(source_path, f"{arch.name}.cpp"), "w", encoding="utf-8") as source:
        source.write(f"#include \"{arch.name}.hpp\"\n\n")
        source.write("#include <algorithm>\n")
        source.write("#include <array>\n")
        source.write("#include <utility>\n\n")
        source.write(f"namespace {arch.name} {{\n\n")
        source.write("struct ValueRange {\n")
        source.write("  std::uint32_t min;\n")
        source.write("  std::uint32_t max;\n")
        source.write("};\n\n")
        source.write("struct EncodingRestriction {\n")
        source.write("  std::uint64_t (*ReadFunc)(std::uint64_t);\n")
        source.write("  const ValueRange* validRanges;\n")
        source.write("  const std::uint32_t rangeCount;\n")
        source.write("  const std::uint32_t isSched = 0u;\n")
        source.write("};\n\n")
        source.write("struct DecodingInfo {\n")
        source.write("  std::uint64_t instMask;\n")
        source.write("  std::uint64_t instValue;\n")
        source.write("  std::uint64_t schedMask;\n")
        source.write("  std::uint64_t schedValue;\n")
        source.write("  const char* opcode;\n")
        source.write("  OpClass opclass;\n")
        source.write("  const EncodingRestriction* restrictions = nullptr;\n")
        source.write("  std::size_t restrictionCount = 0;\n")
        source.write("};\n\n")
        unique_ranges: dict[tuple[ValueRange, ...], str] = {}
        counter: int = 0
        for entry in decoding_info:
            for restriction in entry.restrictions:
                if tuple(restriction.ranges) in unique_ranges:
                    continue
                else:
                    unique_ranges[tuple(restriction.ranges)] = f"sRange{counter}"
                    source.write(f"static constexpr const ValueRange sRange{counter}[] = {{ {", ".join(f"ValueRange{{ {r.min}u, {r.max}u }}" for r in restriction.ranges)}, }};\n")
                    counter += 1
        source.write("\n")
        for entry in decoding_info:
            if len(entry.restrictions) == 0:
                continue
            source.write(f"static constexpr const EncodingRestriction s{fix_name(entry.opclass.name)}Restrictions[] = {{\n")
            for restriction in entry.restrictions:
                # this is not guaranteed but it's easier to deal with if we assume it to be true
                encoding: str = restriction.encoding.encoding if isinstance(restriction.encoding, EncodingField) else restriction.encoding.encodings[0]
                if all(r.start < 64 for r in arch.funit.encodings[encoding]):
                    source.write(f"  EncodingRestriction{{ {f"{fix_name(encoding)}Encoding::Read":<45}, {f"{unique_ranges[tuple(restriction.ranges)]}":<10}, {len(restriction.ranges):<5} }},\n")
                elif all(r.start >= 64 for r in arch.funit.encodings[encoding]):
                    source.write(f"  EncodingRestriction{{ {f"{fix_name(encoding)}Encoding::Read":<45}, {f"{unique_ranges[tuple(restriction.ranges)]}":<10}, {len(restriction.ranges):<5}, 1u }},\n")
                else:
                    raise Exception
            source.write("};\n\n")
        source.write(f"static constexpr const std::array<DecodingInfo, {len(decoding_info) + 1}> sDecodingTable = {{\n")
        # default NOP is the highest priority instruction (there can be normal NOPs as well)
        source.write(f"  DecodingInfo{{ {nop.mask & 0xffffffffffffffff:#018x}ull, {nop.value & 0xffffffffffffffff:#018x}ull, {nop.mask >> 64:#018x}ull, {nop.value >> 64:#018x}ull, {f"\"NOP\"":<15}, {f"OpClass::NOP_DEFAULT":<34} }},\n")
        for entry in decoding_info:
            if len(entry.restrictions) == 0:
                source.write(f"  DecodingInfo{{ {entry.mask.mask & 0xffffffffffffffff:#018x}ull, {entry.mask.value & 0xffffffffffffffff:#018x}ull, {entry.mask.mask >> 64:#018x}ull, {entry.mask.value >> 64:#018x}ull, {f"\"{entry.opcode}\"":<15}, {f"OpClass::{fix_name(entry.opclass.name)}":<34} }},\n")
            else:
                source.write(f"  DecodingInfo{{ {entry.mask.mask & 0xffffffffffffffff:#018x}ull, {entry.mask.value & 0xffffffffffffffff:#018x}ull, {entry.mask.mask >> 64:#018x}ull, {entry.mask.value >> 64:#018x}ull, {f"\"{entry.opcode}\"":<15}, {f"OpClass::{fix_name(entry.opclass.name)}":<34}, {f"s{fix_name(entry.opclass.name)}Restrictions":<40}, {len(entry.restrictions):<5} }},\n")
        source.write("};\n\n")
        source.write("std::optional<const DecodedInstruction> Decode(std::uint64_t inst, std::uint64_t sched) {\n")
        source.write("  for (const auto& entry : sDecodingTable) {\n")
        source.write("    if ((inst & entry.instMask) == entry.instValue && (sched & entry.schedMask) == entry.schedValue) {\n")
        source.write("      if (entry.restrictions == nullptr || entry.restrictionCount == 0)\n")
        source.write("        return std::make_optional<const DecodedInstruction>(inst, sched, entry.opcode, entry.opclass);\n")
        source.write("      if (std::all_of(entry.restrictions, entry.restrictions + entry.restrictionCount, [=](const auto& restriction) {\n")
        source.write("        const std::uint32_t value = static_cast<std::uint32_t>(restriction.ReadFunc(restriction.isSched ? sched : inst));\n")
        source.write("        return std::any_of(restriction.validRanges, restriction.validRanges + restriction.rangeCount, [=](const auto& range) {\n")
        source.write("          return value - range.min < range.max - range.min;\n")
        source.write("        });\n")
        source.write("      })) {\n")
        source.write("        return std::make_optional<const DecodedInstruction>(inst, sched, entry.opcode, entry.opclass);\n")
        source.write("      }\n")
        source.write("    }\n")
        source.write("  }\n")
        source.write("  return std::nullopt;\n")
        source.write("}\n\n")
        source.write("#define TABLE_LOOKUP(table, ...) \\\n")
        source.write("std::optional<std::tuple<__VA_ARGS__>> table(std::uint64_t value) { \\\n")
        source.write("  const auto res = std::lower_bound(s ## table.begin(), s ## table.end(), value, [](const auto& entry, std::uint64_t value) { \\\n")
        source.write("    return entry.first < value; \\\n")
        source.write("  }); \\\n")
        source.write("  return res == s ## table.end() ? std::nullopt : std::make_optional<std::tuple<__VA_ARGS__>>(res->second); \\\n")
        source.write("}\n")
        for table in arch.get_used_tables():
            tbl: Table = arch.tables[table]
            if tbl.lookup_type == 1:
                types: str = ", ".join(fix_name(v.name) if isinstance(v, RegisterGroup) else "std::uint64_t" for v in tbl.arg_types)
                unique_values: list[int] = sorted(set(entry.value for entry in tbl.entries))
                source.write(f"static constexpr const std::array<std::pair<std::uint64_t, std::tuple<{types}>>, {len(unique_values)}> s{fix_name(tbl.name)} = {{\n")
                seen_values: set[int] = set()
                for entry in sorted(tbl.entries, key=lambda entry: entry.value):
                    if entry.value in seen_values:
                        continue
                    seen_values.add(entry.value)
                    value: str = ", ".join(f"{fix_name(arg.group.name)}::{fix_name(arg.name)}" if isinstance(arg, Register) else f"{arg}ull" if isinstance(arg, int) else f"'{arg}'" for arg in entry.arguments)
                    source.write(f"  std::pair{{ {entry.value}ull, std::tuple<{types}>{{ {value} }} }},\n")
                source.write("};\n")
                source.write(f"TABLE_LOOKUP({fix_name(tbl.name)}, {types})\n")
        source.write(f"}} // namespace {arch.name}")
    
    with open(os.path.join(include_path, f"{arch.name}Accessor.hpp"), "w", encoding="utf-8") as header:
        header.write("#pragma once\n\n")
        header.write(f"#include \"{arch.name}.hpp\"\n\n")
        header.write("#include <bit>\n")
        header.write("#include <limits>\n\n")
        header.write(f"namespace {arch.name} {{\n\n")
        header.write(
"""struct AccessorBase {
  std::uint64_t inst;
  std::uint64_t sched;
  std::uint64_t pc;

  constexpr AccessorBase(std::uint64_t _inst, std::uint64_t _sched, std::uint64_t _pc) noexcept : inst(_inst), sched(_sched), pc(_pc) {}

  using ProcessingFunc = std::uint64_t (*)(std::uint64_t, std::uint64_t);

  static constexpr std::uint64_t _Bool(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value & 1ull;
  }

  static constexpr std::uint64_t _Reg(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value & 0xffffull;
  }

  template <std::uint64_t XOR>
  static constexpr std::uint64_t _Xor(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value ^ XOR;
  }

  template <std::uint64_t ROR, std::size_t SIZE>
  static constexpr std::uint64_t _Rotate(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(ROR < SIZE, "Rotation must be less than the size of the field!");
    constexpr std::uint64_t mask = SIZE >= 0x40 ? 0xfffffffffffffff : (1ull << SIZE) - 1;
    return value >> (SIZE - ROR) | value << (ROR) & mask;
  }

  static constexpr std::uint64_t _Pcrel(std::uint64_t value, std::uint64_t programCounter) {
    return value - programCounter - RELATIVE_ADDRESS_BASE;
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _Sext(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(SEXT<SIZE>(value));
  }

  template <std::uint64_t BIAS>
  static constexpr std::uint64_t _Bias(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return value - BIAS;
  }

  static constexpr std::uint64_t _Invert(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(value == 0ull);
  }

  static constexpr std::uint64_t _Negate(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return static_cast<std::uint64_t>(-static_cast<std::int64_t>(value));
  }

  template <std::uint64_t LOG>
  static constexpr std::uint64_t _Log2(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    return 1ull << value;
  }

  template <std::uint64_t FACTOR>
  static constexpr std::uint64_t _Multiply(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(FACTOR != 0, "Multiplicative factor must be non-zero");
    return value / FACTOR;
  }

  template <std::uint64_t FACTOR>
  static constexpr std::uint64_t _Scale(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    static_assert(FACTOR != 0, "Scale factor must be non-zero");
    constexpr std::uint64_t shift = sizeof(std::uint64_t) * CHAR_BIT - std::countl_zero(FACTOR) - 1;
    return value << shift;
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F16(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if constexpr (SIZE < 0x10)
      value <<= 0x10 - SIZE;
    value &= 0xffffull;
    const std::uint64_t sign = value >> 0xf & 1ull;
    const std::uint64_t exp = value >> 10 & 0x1full;
    const std::uint64_t mantissa = value & 0x3ffull;
    std::uint32_t v;
    if (exp == 0x1full) {
      v = (mantissa == 0ull ? 0ull : (mantissa << 0xd | 0x400000ull)) | 0xffull << 0x17 | sign << 0x1f;
    } else if (exp == 0ull) {
      std::uint64_t newMantissa = (mantissa << 0xd) * 2;
      std::uint64_t newExp = 0x70;
      while ((newMantissa & 0x400000ull) == 0ull) {
        newMantissa *= 2; --newExp;
      }
      v = newMantissa & 0x7fffffull | newExp << 0x17 | sign << 0x1f;
    } else {
      v = mantissa << 0xd | exp + 0x70ull << 0x17 | sign << 0x1f;
    }
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F32(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if constexpr (SIZE < 0x20)
      value <<= 0x20 - SIZE;
    const std::uint32_t v = static_cast<std::uint32_t>(value);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <std::size_t SIZE>
  static constexpr std::uint64_t _F64(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    if ((value & 0x7ff0000000000000ull) == 0x7ff0000000000000ull && (value & 0xfffffffffffffull) != 0ull)
      value != 0x8000000000000ull;
    if constexpr (SIZE < 0x40)
      value <<= 0x40 - SIZE;
    return value;
  }

  static constexpr std::uint64_t _E6M9(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint64_t sign = value >> 0xf & 1ull;
    const std::uint64_t exp = value >> 9 & 0x3full;
    const std::uint64_t mantissa = value & 0x1ffull;
    if (exp == 0x3full) {
      return mantissa << 0x2b | 0x7ff0000000000000ull | sign << 0x3f;
    } else if (exp == 0ull) {
      if (mantissa == 0) {
        return sign << 0x3f;
      }
      std::uint64_t newMantissa = (mantissa << 0x2b) * 2;
      std::uint64_t newExp = 0x3e0ull;
      while ((newMantissa >> 0x34 & 1ull) == 0ull) {
        newMantissa *= 2; --newExp;
      }
      return (newMantissa & 0xffefffffffffffffull) | newExp << 0x34 | sign << 0x3f;
    } else {
      return mantissa << 0x2b | (exp + 0x3e0ull) << 0x34 | sign << 0x3f;
    }
  }

  static constexpr std::uint64_t _BF16(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint32_t v = static_cast<std::uint32_t>(value << 0x10);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  static constexpr std::uint64_t _TF32(std::uint64_t value, [[maybe_unused]] std::uint64_t programCounter) {
    const std::uint32_t v = static_cast<std::uint32_t>(value);
    return std::bit_cast<std::uint64_t, double>(static_cast<double>(std::bit_cast<float, std::uint32_t>(v)));
  }

  template <typename Encoding, ProcessingFunc... FUNCS>
  constexpr std::uint64_t GetImpl(std::uint64_t source) const {
    std::uint64_t value = Encoding(source).value();
    ([&](ProcessingFunc func){
      value = func(value, pc); 
    }(FUNCS), ...);
    return value;
  }

};

template <OpClass CLASS> struct Accessor;

#define TABLE_FIELD(source, name, encoding, type, table, index, ...) \\
  type name() const { \\
    const std::uint64_t raw = AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source); \\
    return static_cast<type>(static_cast<std::uint64_t>(std::get<index>(table(raw).value()))); \\
  }
#define INST_TABLE_FIELD(name, encoding, type, table, index, ...) TABLE_FIELD(inst, name, encoding, type, table, index, __VA_ARGS__)
#define SCHED_TABLE_FIELD(name, encoding, type, table, index, ...) TABLE_FIELD(sched, name, encoding, type, table, index, __VA_ARGS__)

#define FIELD(source, name, encoding, type, ...) \\
  type name() const { \\
    return static_cast<type>(AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source)); \\
  }
#define INST_FIELD(name, encoding, type, ...) FIELD(inst, name, encoding, type, __VA_ARGS__)
#define SCHED_FIELD(name, encoding, type, ...) FIELD(sched, name, encoding, type, __VA_ARGS__)

#define SIGNED_FIELD(source, name, encoding, type, ...) \\
  type name() const { \\
    std::uint64_t value = AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source); \\
    if (static_cast<std::int64_t>(value) == std::numeric_limits<std::int64_t>::min()) \\
      return static_cast<type>(0ull); \\
    const bool is_signed = name ## _sign(); \\
    if (value == 0ull) { \\
      return static_cast<type>(static_cast<std::uint64_t>(is_signed) + 1); \\
    } \\
    return static_cast<type>(is_signed ? static_cast<std::uint64_t>(-static_cast<std::int64_t>(value)) : value); \\
  }
#define SIGNED_INST_FIELD(name, encoding, type, ...) SIGNED_FIELD(inst, name, encoding, type, __VA_ARGS__)
#define SIGNED_SCHED_FIELD(name, encoding, type, ...) SIGNED_FIELD(sched, name, encoding, type, __VA_ARGS__)

#define FLOAT_FIELD(source, name, encoding, type, ...) \\
  type name() const { \\
    static_assert(sizeof(type) == 8, \"Floating point type must be eight bytes\"); \\
    return std::bit_cast<type, std::uint64_t>(AccessorBase::GetImpl<encoding __VA_OPT__(,) __VA_ARGS__>(source)); \\
  }
#define FLOAT_INST_FIELD(name, encoding, type, ...) FLOAT_FIELD(inst, name, encoding, type, __VA_ARGS__)
#define FLOAT_SCHED_FIELD(name, encoding, type, ...) FLOAT_FIELD(sched, name, encoding, type, __VA_ARGS__)

#define CONSTANT_FIELD(name, type, value) \\
  type name() const { \\
    return value; \\
  }

template <OpClass CLASS> struct Accessor;

"""
        )
        # accessors should access fields either by encoding name or by field name
        def find_op(ops: list[EncodingOp], op_type: ReferenceType) -> EncodingOp | None:
            for op in ops:
                if op.op_type == op_type:
                    return op
            return None
        def get_post_ops(encoding: EncodingField) -> str:
            fixups: list[str] = []
            if (op := find_op(encoding.encoding_ops, ReferenceType.XOR)) is not None:
                fixups.append(f"_Xor<{op.value}ull>")
            if (op := find_op(encoding.encoding_ops, ReferenceType.ROTATION)) is not None:
                fixups.append(f"_Rotate<{op.value}ull, {sum(r.nbits for r in arch.funit.encodings[encoding.encoding])}>")
            if (op := find_op(encoding.encoding_ops, ReferenceType.SIGN_EXT)) is not None:
                fixups.append(f"_Sext<{sum(r.nbits for r in arch.funit.encodings[encoding.encoding])}>")
            if (op := find_op(encoding.encoding_ops, ReferenceType.INVERT)) is not None:
                fixups.append("_Invert")
            if (op := find_op(encoding.encoding_ops, ReferenceType.NEGATE)) is not None:
                fixups.append("_Negate")
            if (op := find_op(encoding.encoding_ops, ReferenceType.LOG2)) is not None:
                fixups.append(f"_Log2<{op.value}ull>")
            if (op := find_op(encoding.encoding_ops, ReferenceType.PCREL)) is not None:
                fixups.append("_Pcrel")
            if (op := find_op(encoding.encoding_ops, ReferenceType.SCALE)) is not None:
                fixups.append(f"_Scale<{op.value}ull>")
            if (op := find_op(encoding.encoding_ops, ReferenceType.MULTIPLY)) is not None:
                fixups.append(f"_Multiply<{op.value}ull>")
            if fixups:
                return f", {", ".join(f"Accessor::{fixup}" for fixup in fixups)}"
            else:
                return ""
        def handle_register_modifier(modifier: OperandField, field: RegisterOperand | ImmediateOperand, opclass: OperationClass) -> None:
            modifier_name: str = {
                OperandField.NOT : "not",
                OperandField.INVERT : "invert",
                OperandField.NEGATE : "negate",
                OperandField.ABSOLUTE : "absolute",
                OperandField.SIGN : "sign",
            }[modifier]
            name: str = f"{fix_name(field.name)}@{modifier_name}"
            if name not in opclass.encoded_fields:
                return
            encoding: EncodingField | MultiEncodingField = opclass.encoded_fields[name]
            if isinstance(encoding, EncodingField):
                macro: str = "INST_FIELD" if all(r.start < 64 for r in arch.funit.encodings[encoding.encoding]) else "SCHED_FIELD"
                header.write(f"  {macro}({fix_name(name).replace("@", "_")}, {fix_name(encoding.encoding)}Encoding, bool{get_post_ops(encoding)}, Accessor::_Bool)\n")
            else:
                if arch.tables[encoding.table].lookup_type == 1:
                    macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                    index: int = -1
                    for i, arg in enumerate(encoding.arguments):
                        if arg.value == field and arg.field == modifier:
                            index = i
                            break
                    if index == -1:
                        raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                    header.write(f"  {macro}({fix_name(name).replace("@", "_")}, MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>, bool, {encoding.table}, {index}, Accessor::_Bool)\n")
        def handle_register_operand(field: RegisterOperand, opclass: OperationClass) -> None:
            if field.name in opclass.encoded_fields or field.register.name in opclass.encoded_fields:
                encoding: EncodingField | MultiEncodingField
                if field.name in opclass.encoded_fields:
                    encoding = opclass.encoded_fields[field.name]
                else:
                    encoding = opclass.encoded_fields[field.register.name]
                if isinstance(encoding, EncodingField):
                    macro: str = "INST_FIELD" if all(r.start < 64 for r in arch.funit.encodings[encoding.encoding]) else "SCHED_FIELD"
                    if field.fields is not None and OperandField.SIGN in field.fields:
                        macro = f"SIGNED_{macro}"
                    header.write(f"  {macro}({fix_name(field.name)}, {fix_name(encoding.encoding)}Encoding, {fix_name(field.register.name)}{get_post_ops(encoding)}, Accessor::_Reg)\n")
                else:
                    if arch.tables[encoding.table].lookup_type == 1:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        header.write(f"  {macro}({fix_name(field.name)}, MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>, {fix_name(field.register.name)}, {encoding.table}, {index}, Accessor::_Reg)\n")
                    elif arch.tables[encoding.table].lookup_type == 0:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        header.write(f"  {macro}({fix_name(field.name)}, MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>, {fix_name(field.register.name)}, {encoding.table}<{fix_name(field.register.name)}>, {index}, Accessor::_Reg)\n")
                    elif arch.tables[encoding.table].lookup_type in [11, 12]:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        # workaround for commas in typename passed to macro
                        header.write(f"  using {fix_name(field.name)}Encoding = MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>;\n")
                        assert isinstance(encoding.arguments[1].value, ImmediateOperand), f"Offset for const banks must be an immediate!"
                        bitwidth: int = encoding.arguments[1].value.bitwidth
                        header.write(f"  {macro}({fix_name(field.name)}, {fix_name(field.name)}Encoding, {fix_name(field.register.name)}, {encoding.table}<{bitwidth}>, {index}, Accessor::_Reg)\n")
                    else:
                        raise ValueError(f"Unsupported table type: {encoding.table} ({arch.tables[encoding.table].lookup_type})")
            else:
                if field.default is not None:
                    header.write(f"  CONSTANT_FIELD({fix_name(field.name)}, {fix_name(field.register.name)}, {fix_name(field.default.group.name)}::{fix_name(field.default.name)})\n")
                # otherwise the field only exists to have modifiers
            if field.fields is not None:
                for modifier in field.fields:
                    handle_register_modifier(modifier, field, opclass)
        def get_immediate_typename(field: ImmediateOperand) -> str:
            match (field.imm_type):
                case ImmediateType.Integer:
                    if field.bitwidth > 32:
                        return "std::int64_t" if field.signed else "std::uint64_t"
                    elif field.bitwidth > 16:
                        return "std::int32_t" if field.signed else "std::uint32_t"
                    elif field.bitwidth > 8:
                        return "std::int16_t" if field.signed else "std::uint16_t"
                    else:
                        return "std::int8_t" if field.signed else "std::uint8_t"
                case ImmediateType.Bitset:
                    if field.bitwidth > 32:
                        return "std::uint64_t"
                    elif field.bitwidth > 16:
                        return "std::uint32_t"
                    elif field.bitwidth > 8:
                        return "std::uint16_t"
                    else:
                        return "std::uint8_t"
                case _:
                    return "double"
        def handle_immediate_operand(field: ImmediateOperand, opclass: OperationClass) -> None:
            if field.name in opclass.encoded_fields:
                encoding: EncodingField | MultiEncodingField = opclass.encoded_fields[field.name]
                typename: str = get_immediate_typename(field)
                if isinstance(encoding, EncodingField):
                    macro: str = "INST_FIELD" if all(r.start < 64 for r in arch.funit.encodings[encoding.encoding]) else "SCHED_FIELD"
                    if typename == "double":
                        macro = f"FLOAT_{macro}"
                    elif field.fields is not None and OperandField.SIGN in field.fields and f"{fix_name(field.name)}@sign" in opclass.encoded_fields:
                        macro = f"SIGNED_{macro}"
                    header.write(f"  {macro}({fix_name(field.name)}, {fix_name(encoding.encoding)}Encoding, {typename}{get_post_ops(encoding)})\n")
                else:
                    if arch.tables[encoding.table].lookup_type == 1:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        header.write(f"  {macro}({fix_name(field.name)}, MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>, {typename}, {encoding.table}, {index})\n")
                    elif arch.tables[encoding.table].lookup_type == 0:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        header.write(f"  {macro}({fix_name(field.name)}, MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>, {typename}, {encoding.table}<{typename}>, {index})\n")
                    elif arch.tables[encoding.table].lookup_type in [11, 12]:
                        macro: str = "INST_TABLE_FIELD" if all(r.start < 64 for enc in encoding.encodings for r in arch.funit.encodings[enc]) else "SCHED_TABLE_FIELD"
                        index: int = -1
                        for i, arg in enumerate(encoding.arguments):
                            if arg.value == field:
                                index = i
                                break
                        if index == -1:
                            raise ValueError("Could not find field index", field.name, opclass.name, encoding.table)
                        # workaround for commas in typename passed to macro
                        header.write(f"  using {fix_name(field.name)}Encoding = MultiEncoding<{",".join(f"{fix_name(e)}Encoding" for e in encoding.encodings)}>;\n")
                        assert isinstance(encoding.arguments[1].value, ImmediateOperand), f"Offset for const banks must be an immediate!"
                        bitwidth: int = encoding.arguments[1].value.bitwidth
                        header.write(f"  {macro}({fix_name(field.name)}, {fix_name(field.name)}Encoding, {typename}, {encoding.table}<{bitwidth}>, {index})\n")
                    else:
                        raise ValueError(f"Unsupported table type: {encoding.table} ({arch.tables[encoding.table].lookup_type})")
            else:
                if field.default is not None:
                    header.write(f"  CONSTANT_FIELD({fix_name(field.name)}, {typename}, {field.default})\n")
                # otherwise the field only exists to have modifiers
            if field.fields is not None:
                for modifier in field.fields:
                    handle_register_modifier(modifier, field, opclass)
        header.write("template <> struct Accessor<OpClass::NOP_DEFAULT> : public AccessorBase { using AccessorBase::AccessorBase; };\n\n")
        for name, opclass in arch.funit.op_classes.items():
            header.write(f"template <> struct Accessor<OpClass::{fix_name(name)}> : public AccessorBase {{\n")
            header.write("  using AccessorBase::AccessorBase;\n")
            for op in opclass.format:
                for field in arch.get_encodable_fields(op, False):
                    if isinstance(field, OpcodeOperand):
                        header.write(f"  CONSTANT_FIELD(Opcode, std::uint64_t, {list(opclass.opcodes.values())[0]:#b});\n")
                    elif isinstance(field, RegisterOperand):
                        handle_register_operand(field, opclass)
                    else:
                        handle_immediate_operand(field, opclass)
            header.write("};\n\n")
        header.write(f"}} // namespace {arch.name}")

if __name__ == "__main__":
    import argparse
    import os
    from pathlib import Path

    parser: argparse.ArgumentParser = argparse.ArgumentParser(prog="Machine Description")
    parser.add_argument("--md", help="Path to input machine description file", default="data/SM52.md")
    parser.add_argument("--src", help="Path to source directory", default="src")
    parser.add_argument("--inc", help="Path to include directory", default="src/include")

    args, _ = parser.parse_known_args()
    os.makedirs(args.src, exist_ok=True)
    os.makedirs(args.inc, exist_ok=True)

    arch: Architecture = Architecture.load(Path(args.md).read_text())

    write_file(args.inc, args.src, arch)