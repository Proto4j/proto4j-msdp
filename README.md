# proto4j-msdp
Multicast Service Discovery Protocol (MSDP) specification and implementation in C++ and and Java (with proto4j-xtral).

Spec:

    ┌───────────────────────────────────────────────────────────────────────────────────────┐
    │ MSDP-Packet                                                                           │
    ├─────────────┬──────────────────┬─────────────────┬─────────────────┬──────────────────┤
    │ type: uint8 │ system_id: uint8 │ version: uint16 │ uuid: uint8[12] │ checksum: uint16 │
    ├─────────────┴──┬───────────────┴─────────────────┴─────────────────┴──────────────────┤
    │ length: uint32 │ payload: uint8[]                                                     │
    └────────────────┴──────────────────────────────────────────────────────────────────────┘
